#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

// Node structure for each song
struct SongNode {
    string singer;
    string title;
    SongNode* next;

    SongNode(string s, string t, SongNode* n = nullptr) : singer(s), title(t), next(n) {}
};

// Playlist map to manage multiple playlists
map<string, SongNode*> playlists;

// Function prototypes
void addSong(SongNode*& head, const string& singer, const string& title);
void removeSong(SongNode*& head, const string& title);
void displayPlaylist(SongNode* head);
void sortPlaylist(SongNode*& head, bool byTitle);
void savePlaylist(SongNode* head, const string& filename);
void loadPlaylist(SongNode*& head, const string& filename);
void deletePlaylist(SongNode*& head);
void managePlaylists();

int main() {
    managePlaylists();
    return 0;
}

void managePlaylists() {
    int choice;

    while (true) {
        cout << "\n===================================\n"
             << "Spotify-like Playlist Application\n"
             << "===================================\n"
             << "1. Create New Playlist\n"
             << "2. Select Existing Playlist\n"
             << "3. Display All Playlists\n"
             << "4. Delete Playlist\n"
             << "5. Exit\n"
             << "Enter your choice: ";
        cin >> choice;

        if (choice == 5) {
            cout << "Exiting application." << endl;
            break;
        }

        string playlistName;

        switch (choice) {
            case 1:
                cout << "Enter new playlist name: ";
                cin.ignore();
                getline(cin, playlistName);
                if (playlists.find(playlistName) == playlists.end()) {
                    playlists[playlistName] = nullptr;
                    cout << "Playlist created: " << playlistName << endl;
                } else {
                    cout << "Playlist already exists." << endl;
                }
                break;

            case 2:
                cout << "Enter playlist name to manage: ";
                cin.ignore();
                getline(cin, playlistName);
                if (playlists.find(playlistName) != playlists.end()) {
                    SongNode*& selectedPlaylist = playlists[playlistName];
                    int subChoice;
                    while (true) {
                        cout << "\nManaging Playlist: " << playlistName << endl;
                        cout << "1. Add Song\n"
                             << "2. Remove Song\n"
                             << "3. Display Songs\n"
                             << "4. Sort by Title\n"
                             << "5. Sort by Singer\n"
                             << "6. Save to File\n"
                             << "7. Load from File\n"
                             << "8. Go Back\n"
                             << "Enter your choice: ";
                        cin >> subChoice;

                        if (subChoice == 8) break;

                        string title, singer, filename;

                        switch (subChoice) {
                               case 1:
                                cout << "Enter song title: ";
                                cin.ignore();
                                getline(cin, title);
                                cout << "Enter singer: ";
                                getline(cin, singer);
                                addSong(selectedPlaylist, singer, title);
                                break;

                            case 2:
                                cout << "Enter song title to remove: ";
                                cin.ignore();
                                getline(cin, title);
                                removeSong(selectedPlaylist, title);
                                break;

                            case 3:
                                displayPlaylist(selectedPlaylist);
                                break;

                            case 4:
                                sortPlaylist(selectedPlaylist, true);
                                break;

                            case 5:
                                sortPlaylist(selectedPlaylist, false);
                                break;

                            case 6:
                                cout << "Enter filename to save to: ";
                                cin.ignore();
                                getline(cin, filename);
                                savePlaylist(selectedPlaylist, filename);
                                break;

                            case 7:
                                cout << "Enter filename to load from: ";
                                cin.ignore();
                                getline(cin, filename);
                                loadPlaylist(selectedPlaylist, filename);
                                break;

                            default:
                                cout << "Invalid choice. Please try again." << endl;
                                break;
                        }
                    }
                } else {
                    cout << "Playlist not found: " << playlistName << endl;
                }
                break;

            case 3:
                if (playlists.empty()) {
                    cout << "No playlists available." << endl;
                } else {
                    cout << "Available Playlists:" << endl;
                    for (const auto& pair : playlists) {
                        cout << "- " << pair.first << endl;
                    }
                }
                break;

            case 4:
                cout << "Enter playlist name to delete: ";
                cin.ignore();
                getline(cin, playlistName);
                if (playlists.find(playlistName) != playlists.end()) {
                    deletePlaylist(playlists[playlistName]);
                    playlists.erase(playlistName);
                    cout << "Playlist deleted: " << playlistName << endl;
                } else {
                    cout << "Playlist not found: " << playlistName << endl;
                }
                break;

            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }

    // Clean up all playlists
    for (auto& pair : playlists) {
        deletePlaylist(pair.second);
    }
}

// Song management functions
void addSong(SongNode*& head, const string& singer, const string& title) {
    SongNode* newNode = new SongNode(singer, title);
    if (head == nullptr) {
        head = newNode;
    } else {
        SongNode* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
    cout << "Song added: " << title << " by " << singer << endl;
}

void removeSong(SongNode*& head, const string& title) {
    if (head == nullptr) {
        cout << "Playlist is empty." << endl;
        return;
    }
    if (head->title == title) {
        SongNode* temp = head;
        head = head->next;
        delete temp;
        cout << "Removed song: " << title << endl;
        return;
    }
    SongNode* current = head;
    while (current->next != nullptr && current->next->title != title) {
        current = current->next;
    }
    if (current->next == nullptr) {
        cout << "Song not found: " << title << endl;
    } else {
        SongNode* temp = current->next;
        current->next = current->next->next;
        delete temp;
        cout << "Removed song: " << title << endl;
    }
}

void displayPlaylist(SongNode* head) {
    if (head == nullptr) {
        cout << "Playlist is empty." << endl;
        return;
    }
    cout << "Playlist Songs:" << endl;
    while (head != nullptr) {
        cout << "Title: " << head->title << ", Singer: " << head->singer << endl;
        head = head->next;
    }
}

void sortPlaylist(SongNode*& head, bool byTitle) {
    if (head == nullptr || head->next == nullptr) {
        return;
    }
    bool swapped;
    do {
        swapped = false;
        SongNode* current = head;
        while (current->next != nullptr) {
            SongNode* next = current->next;
            if ((byTitle && current->title > next->title) || (!byTitle && current->singer > next->singer)) {
                swap(current->title, next->title);
                swap(current->singer, next->singer);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
    cout << "Playlist sorted by " << (byTitle ? "title" : "singer") << "." << endl;
}

void savePlaylist(SongNode* head, const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Error opening file for writing: " << filename << endl;
        return;
    }
    while (head != nullptr) {
        outFile << head->title << "," << head->singer << endl;
        head = head->next;
    }
    outFile.close();
    cout << "Playlist saved to " << filename << endl;
}

void loadPlaylist(SongNode*& head, const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Error opening file for reading: " << filename << endl;
        return;
    }
    string title, singer;
    while (getline(inFile, title, ',') && getline(inFile, singer)) {
        addSong(head, singer, title);
    }
    inFile.close();
    cout << "Playlist loaded from " << filename << endl;
}

void deletePlaylist(SongNode*& head) {
    while (head != nullptr) {
        SongNode* temp = head;
        head = head->next;
        delete temp;
    }
}