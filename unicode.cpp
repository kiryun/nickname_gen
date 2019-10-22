#include <bits/stdc++.h>

using namespace std;

int main()
{

    u16string in = u"김기현";

    string s;
    cin>>s;
    
    stringstream out;

    int arr[3];

    int i = 0;
    for (auto x : in){

        out << hex << "U+" << x << " ";
        arr[i] = x;
        i++;
    }
    
    cout<<endl;

    cout << out.str();
    cout<<endl;

    for(int i = 0; i<sizeof(arr)/sizeof(int); i++){
        printf("%x ", arr[i]);
        // cout<<arr[i]<<" ";
    }
    cout<<endl;
    return 0;
}

// int main(){
//     // setlocale(LC_ALL, "Korean");
//     wchar_t* name = new wchar_t[255];
//     wscanf(L"%ls", name);
    
//     wprintf(L"%ls\n", name);
//     // wprintf(L"%d\n", wcslen(name));

//     //unicode hex
//     int i = 0;
//     while(name[i] != NULL){

//         printf("%x ",name[i]);
//         i++;
//     }
//     printf("\n");

//     //unicode hex point
    

//     return 0;
// }
