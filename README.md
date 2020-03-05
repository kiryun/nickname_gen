# nickname_gen
https://velog.io/@wimes/Nickname-생성기-p6k2342cfn
## 개요

c++을 이용해 nick name(별명)을 생성할 것 입니다.

필요 리소스는 본인의 이름뿐 입니다.

예를 들어 "홍길동"의 이름을 넣으면

홍길동에서 추출할 수있는 알파벳을 추출합니다.

알파벳의 조합을 이용해 \<nick name\> 이 될 수 있는 경우의 수를 모두 보여줍니다.

사용자는 그 중에서 마음에 드는 닉네임을 고르면 됩니다.

## 알고리즘

\<nick name\>은 다음의 알고리즘을 따릅니다.

### 이름 입력

사용자의 이름을 unicode로 입력받고 저장합니다.

예를 들어 "홍길동"이라는 이름을 입력했다고 가정합니다.

"홍길동"을 unicode로 변환하면 0xD64D(홍) 0xAE38(길) 0xB3D9(동) 으로 변환됩니다.

### 알파벳 추출

추출된 uunicode를 이용해 알파벳을 추출 할 것입니다.

3글자의 unicode로 이루어진 이름을 1byte로 쪼개서 저장합니다.

0xD6 0x4D 0xAE 0x38 0xB3 0xD9

이름을 10진수 26으로 나눈 나머지에 97을 더합니다.

`alphabet[i] = ( alphabet[i] % 26 ) + 97`

D6 -> 6 + 97 = 103 = g

4D -> 25 + 97 = 122 = z

AE -> 18 + 97 = 115 = s

38 -> 4 + 97 = 101 = e

B3 -> 23 + 97 = 120 = x

D9 -> 9 + 97 = 106 = j

`alphabet = {g, z, s, e, x, j}`를 추출 했습니다.

### 조합

**모음: a e i o u y**

**자음: 모음외 나머지 알파벳**

1. 만약 모음이 2개미만이라면, 사용자는 모음하나를 추가해야한다.
   -> 알파벳 집합에서 모음있는지 찾아야함
2. 사용자는 5~7사이의 nickname길이를 정해야한다.
3. 모음은 연속을 허용한다.(ai, ae, aie, aoue 등 가능 )
   -> 
4. 자음은 선택적 연속을 허용한다.(tt, ss 등 가능, ts, bt 등 불가능)
   -> 이전에 문자가 자음이었는지 알아봐야함. 현재문자와 비교
5. 각 문자는 뒤에 같은 글자 최대 1번까지 올 수 있다.(단어내에 ee, ii, bb, cc, tt 등 존재가능) 그 이후에는 자음또는 모음이 와야한다.(단어내에 eee, iii, ttt, bbb 등은 존재할 수 없다.)
   -> 이전에 문자가 현재의 문자와 같다면 `연속성 count` +1 한다. `연속성 count`가 만약 2라면 안됨
6. h는 자음+자음에서 wild카드이다.(bh, ch 가능/bbh, tth는 불가능)
   ->이전에 h가 나왔다면 같은 단어가 나온것으로 취급(연속적이다 취급)



## 소스코드

**개발환경**

1) OS: MacOS 10.15

2) Language: C++ 11

3) Compiler: g++ 4.2.1


![image-20191022185434822.png](https://images.velog.io/post-images/wimes/9b657c20-f57c-11e9-b0d9-e36969e4a710/image-20191022185434822.png)


```c++
#include <bits/stdc++.h>

#define MAX 255

using namespace std;

//모음 모음
char vowel[6] = {'a', 'e', 'i', 'o', 'u', 'y'};

//입력받은 이름
//이름에서 추출된 알파벳
uint16_t name[MAX] = {NULL, };
char alphabet[MAX] = {NULL, };

//나올 수 있는 단어의 최대 길이
int len = 0;
//dfs 순회중 방문한 곳
bool visit[MAX] = {false, };
//결과가 저장되는 곳
vector<char> result;
//결과 길이 정하기
int r_len = 0;

template<typename T>
int arrLen(T* arr)
{
	int i = 0;
	while (arr[i] != NULL)
	{
		i++;
	}
	return i;
}

void split(uint16_t* source, uint8_t* result)
{
    int source_len = arrLen(source);
    int src = 0;
    int splt = 0;

    while(source[src] != NULL){
        if(splt % 2){
            result[splt] = source[src] & 0x00ff;
            src++;
        }else{
            result[splt] = source[src] >> 8;
        }
        splt++;
    }
}

void Print()
{
    ofstream out("nick.txt", ios::app);

    //result 배열에 저장된 문자 수 만큼 순회
    for(int i = 0; i<result.size(); i++){
        if(out.is_open()){
            out<<result[i];
        }
        cout<<result[i];
    }
    out<<"\n";
    cout<<"\n";
}

bool isVowel(char c)
{
    if( c == 'a' or
    c == 'e' or
    c == 'i' or
    c == 'o' or
    c == 'u' or
    c == 'y' ){
        return true;
    }    
    return false;
}

//자음인가
bool isConsonant(char c)
{
    if(!isVowel(c)){
        return true;
    }
    return false;
}

//모두 사용했는가
bool usingAll()
{
    for(int i = 0; i<len; i++){
        if(!visit[i]){
            return false;
        }
    }
    return true;
}

//dfs
//idx: 배열 순회중 인덱스 어디까지 왔는지
//last: result배열의 가장 최근에 넣은 idx+1
//continuous: 문자 연속 count
void gen(int idx, int last, int continuous)
{
    //탈출조건
    //알파벳 다 썼을 때
    if(result.size() == r_len){
        //출력 후 리턴
        // cout<<"usingAll"<<endl;
        Print();
        return;
    }

    //alphabet 배열 전체를 순회
    for(int i = 0; i<len; i++){
        // cout<<i<<endl;
        if(visit[i]){
            continue;
        }
        
        if(last == 0){
            visit[i] = true;
            result.push_back(alphabet[i]);

            gen(i, last+1, continuous);

            visit[i] = false;
            result.pop_back();
        }else{
            //어떤 문자도 같은 문자 3개는 안됨
            if(continuous > 1){
                // cout<<"continuous > 1"<<endl;
                continue;
            }

            //이전에 넣은 값과 현재 보고있는 값이 같거나
            //이전에 넣은 값이 자음이면서 현재 보고있는 값이 h라면
            if( (result[last-1] == alphabet[i]) or
            (isConsonant(result[last-1]) and alphabet[i] == 'h')){
                visit[i] = true;
                result.push_back(alphabet[i]);
                continuous += 1;

                // //현재도 자음이고 남은 것도 자음밖에 없다면
                // bool con = true;
                // for(int i = 0; i<len; i++){
                //     if(!visit[i]){
                //         if(isVowel(alphabet[i])){
                //             con = false;
                //         }
                //     }
                // }
                // //출력 후 return
                // if(con && isConsonant( alphabet[i]) ){
                //     Print();
                //     return;
                // }

                gen(i, last+1, continuous);

                visit[i] = false;
                result.pop_back();
                continuous -= 1;
            }else{
                //이전에 넣은게 자음이고 현재도 자음이라면
                if(isConsonant(result[last-1]) & isConsonant(alphabet[i])){
                    // cout<<"자음+자음"<<endl;
                    continue;
                }

                visit[i] = true;
                result.push_back(alphabet[i]);
                int temp = continuous;
                continuous = 0;

                //남은게 자음밖에 없으며
                //

                gen(i, last+1, continuous);

                visit[i] = false;
                result.pop_back();
                continuous = temp;
            }
        }
    }
    
    // Print();
    // return;

}

void testPrint(uint8_t* name_code)
{
    int i = 0;
    while(name[i] != NULL){
        cout<<name[i]<<" ";
        i++;
    }
    cout<<endl;

    i = 0;
    while(name_code[i] != NULL){
        cout<<name_code[i]<<" ";
        i++;
    }
    cout<<endl;

    i = 0;
    while(alphabet[i] != NULL){
        cout<<alphabet[i]<<" ";
        i++;
    }
    cout<<endl;

    i = 0;
    while(alphabet[i] != NULL){
        cout<<visit[i]<<" ";
        i++;
    }
    cout<<endl;
}

int main()
{
    u16string in = u"yourname";
    stringstream out;

    uint8_t name_code[MAX] = {NULL, };

    // for(int i = 0; i<MAX; i++){
    //     name[i] = NULL;
    //     name_code[i] = NULL;
    //     visit[i] = NULL;
    // }

    for(int i = 0; i<in.size(); i++){
        name[i] = in[i];
    }

    split(name, name_code);

    int k = 0;
    while(name_code[k] != NULL){
        // cout<<k<<endl;
        alphabet[k] = (name_code[k] % 26) + 97;
        k++;
    }


    //추출한 alphabet 길이
    while(alphabet[len] != NULL){
        // cout<<len<<endl;
        len++;
    }

    //만약 모음이 2개 미만이라면 모음을 하나더 입력한다.
    int vowel_cnt = 0;
    for(int i = 0; i<len; i++){
        if( isVowel(alphabet[i]) ){
            // cout<<"vowel++"<<endl;
            vowel_cnt++;
        }
    }
    
    while(vowel_cnt < 2){
        char c = 0;
        cout<<"add vowel: ";
        cin>>c;

        //모음을 입력했다면 추가하고 break
        if(isVowel(c)){
            alphabet[len] = c;
            len += 1;
            vowel_cnt++;
        }else{
            cout<<"plz input vowel"<<endl;
        }
    }

    while(true){
        int temp = 0;
        cout<<"nickname length?(5~7)";
        cin>>temp;

        if(temp >= 5 && temp <= 7){
            r_len = temp;
            break;
        }else{
            cout<<"invalid input"<<endl;
        }

    }
    // testPrint(name_code);
    
    gen(0, 0, 0);

    return 0;
}


```

## 최종: github link, nickname
**내가 선택한 닉네임 집합**
```
ssemu*
ssume*
wemus*
weuss*
gewus*
geuss*
guwem*
guess*
usseg*
ugess*
ssuwem*
ssuweg*
weguss*
gessum*
gemuss*
sewim*
wessi*
**wimes**
gemiss*
gewiss*
```
이중에서 나는 **wimes**를 사용하기로 했습니다.

github link: https://github.com/kiryun/nickname_gen










