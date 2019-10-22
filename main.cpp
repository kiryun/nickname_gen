#include <bits/stdc++.h>

using namespace std;

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

void dfs()
{
    
}

int main()
{
    u16string in = u"김기현";
    stringstream out;
    uint16_t name[3];
    uint8_t name_code[6];

    char alphabet[6];

    for(int i = 0; i<in.size(); i++){
        name[i] = in[i];
    }

    split(name, name_code);

    for(int i = 0; i<sizeof(name_code)/sizeof(uint8_t); i++){
        alphabet[i] = (name_code[i] % 26) + 97;
    }
    


    /*
    for(int i = 0; i<sizeof(name)/sizeof(uint16_t); i++){
        printf("%x ", name[i]);
    }
    cout<<endl;

    for(int i = 0; i<sizeof(name_code)/sizeof(uint8_t); i++){
        printf("%x ", name_code[i]);
    }
    cout<<endl;
    
    for(int i = 0; i<sizeof(alphabet)/sizeof(char); i++){
        printf("%c ", alphabet[i]);
    }
    */



    return 0;
}

