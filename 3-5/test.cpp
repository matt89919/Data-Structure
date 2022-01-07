#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;
const int INF = 99999999;
int **adjacency_matrix;
bool *visited;
int *parent;
int *dist;


/* memory allocation*/
void init_2d_array(int** &matrix, int matrix_size)
{
    matrix = new int*[matrix_size];
    for (int i = 0; i < matrix_size; i ++){
        matrix[i] = new int[matrix_size];
        for (int j = 0; j < matrix_size; j ++){
            matrix[i][j] = INF;
            if (i==j)   matrix[i][j] = 0;
        }
    }
}
/* free the memory */
void destruct_2d_array(int** &matrix, int matrix_size)
{
    for(int i = 0; i < matrix_size; i++)
    {
        delete [] matrix[i];
    }
    delete [] matrix;
}
/* for debugging */
void print_matrix(int** matrix, int matrix_size)
{
    for(int i=0; i<matrix_size; i++)
    {
        for(int j=0; j<matrix_size; j++)
        {
            cout<< setw(9) << matrix[i][j]  << setiosflags(ios::right) ;
        }
        cout << endl;
    }
}
/* get nearest node from those haven't been visited*/
int get_nearest(int num_of_vertices)
{
    int min = INF;
    int nearest_node = -1;
    for(int i=0;i<num_of_vertices;i++)
    {
        if((visited[i]==false) && (dist[i] < min))
        {
            min = dist[i];
            nearest_node = i;
        }
    }
    return nearest_node;
}

/* find shortest path */
void dijkstra(int num_of_vertices)
{
    for(int i=0;i<num_of_vertices;i++)
    {
        int nearest = get_nearest(num_of_vertices);
        if (nearest==-1) return;
        visited[nearest] = true;
        for (int j=0; j<num_of_vertices; j++)
        {
            if((adjacency_matrix[nearest][j] != INF) && (dist[j]>dist[nearest]+adjacency_matrix[nearest][j]))
            {
                dist[j] = dist[nearest]+adjacency_matrix[nearest][j];              
                parent[j] = nearest;
            }
        }
    }
}

void output_file(int num_of_vertices, string filename)
{
    ofstream file_out;
    filename.replace(filename.find("in"), 2, "out");
    file_out.open(filename.c_str());
    for(int i=0; i<num_of_vertices; i++)
    {
        file_out << i+1 <<" " << dist[i] << endl;
    }
    file_out.close();
}

int main()
{   
    int num_of_vertices;
    int v1,v2,weight,root;
    string filename;
    ifstream file_in;
    
    cout << "please input filename: ";
    cin >> filename;
    file_in.open(filename.c_str(), ios::in);

    /* get num of vertices*/
    file_in >> num_of_vertices;

    /* initializing the arrays*/
    visited = new bool[num_of_vertices];
    parent = new int[num_of_vertices];
    dist = new int[num_of_vertices];
    for(int i = 0;i<num_of_vertices;i++)
    {
        parent[i] = i;
        dist[i] = INF;
    }
    cout << num_of_vertices << endl;
    init_2d_array(adjacency_matrix, num_of_vertices);

    /* get each vertex pair and its weight*/
    for (int i=0; i<num_of_vertices-1; i++)
    {
        file_in >> v1 >> v2 >> weight;
        adjacency_matrix[v1-1][v2-1] = weight;
        adjacency_matrix[v2-1][v1-1] = weight;
        cout << v1 << " " << v2 << " " << weight << endl;
    }

    /* get root vertex*/
    file_in >> root;
    dist[root-1] = 0;
    cout << root << endl;
    file_in.close();

    dijkstra(num_of_vertices);
    output_file(num_of_vertices, filename);

    /* (test) print adjacency matrix*/
    print_matrix(adjacency_matrix, num_of_vertices);
    destruct_2d_array(adjacency_matrix, num_of_vertices);
    delete [] parent;
    delete [] visited;
    delete [] dist;
    return 0;
}