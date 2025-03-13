#include<iostream>
#include<fstream>
#include<string>
using namespace std;

struct Node
{ 
    string singer;
    string title;
    Node *next;
};

void addList(Node *&head, string singer, string title)
{
    Node *newNode = new Node();
    newNode->singer = singer;
    newNode->title = title;

    // Jadikan newNode sebagai head yang baru.
    newNode->next = head;
    head = newNode;
}
vvoid removeSong(string title) {
    if (!head) {
        cout << "Playlist is empty!" << endl;
        return;
void printList(Node *head)
{
    // Print list dengan perulangan hingga node terakhir.
    cout << endl
         << "===================================" << endl;
    cout << "Playlist :" << endl;
    int index = 1;
    while (head != nullptr)
    {
        cout << "->\t" << "[" << index << ".]\t" << head->singer << " - " << head->title << endl;
        
        head = head->next;
        index++;
    }
    cout << "===================================" << endl
         << endl; 
}

int main()
{
    cout << "===================================" << endl
    cout << "            Mini Spotipa           "
    return 0;
}
