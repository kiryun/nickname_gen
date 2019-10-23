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

