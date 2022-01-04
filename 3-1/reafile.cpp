#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <queue>
#include <stack>
#include <cstring>
using namespace std;    
    
int main(){ 
    int num_of_dataset;
    int matrix_size;
    int entry_index;
    char *token;

    ifstream ifs;
    char buffer[1024] = {0};
    string file_name;
    cout << "pleas enter filename : ";
    cin >> file_name;

    ifs.open(file_name.c_str());
    if (!ifs.is_open()) {
        cout << "Failed to open file.\n";
    } 
    else {
        ifs.getline(buffer, sizeof(buffer));
        num_of_dataset = atoi(buffer); //convert string to integer
        cout<<num_of_dataset<<endl;
        for (int i = 0; i < num_of_dataset; i++)
        {
            ifs.getline(buffer, sizeof(buffer));
            token = strtok(buffer, " ");
            matrix_size = atoi(token);
            token = strtok(NULL, " ");
            entry_index = atoi(token);
            cout << matrix_size << " " << entry_index << endl;
            for (int j = 0; j < matrix_size; j++)
            {
                ifs.getline(buffer, sizeof(buffer));
                token = strtok(buffer, " ");
                cout << token << " ";
                while (1)
                {
                    token = strtok(NULL, " ");
                    if (token==NULL)    break;
                    cout << atoi(token) << " ";
                } 
                cout << endl;
            }
        }
        ifs.close();
    }
}