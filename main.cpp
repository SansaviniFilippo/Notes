#include <iostream>
#include <map>
#include <string>
#include "Note.h"
#include "NotesCollection.h"
#include "ImportantNotesCollection.h"
#include "App.h"

int main() {

    std::cout << "Welcome!" << std::endl;

    bool createCollections = true;
    std::map<std::string, NotesCollection> collections;
    ImportantNotesCollection importantNotesCollection;
    App app;

    while(createCollections) {
        std::cout << "Enter 1 to create a new regular notes collection, 2 to create a new important notes collection, or 3 to exit : " << std::endl;
        int result;
        std::cin >> result;

        switch (result) {
            case 1: {
                std::string collectionName;
                std::cout << "Enter the name : " << std::endl;
                std::cin >> collectionName;

                NotesCollection collectionOne(collectionName);
                collections.insert(std::make_pair(collectionName, collectionOne));
                app.attach(&collectionOne);

                std::cout << "Regular notes collection '" << collectionName << "' created successfully!" << std::endl;
                break;
            }

            case 2: {
                if(importantNotesCollection.getName().empty()) {
                    std::string collectionName;
                    std::cout << "Enter the name of the important notes collection : " << std::endl;
                    std::cin >> collectionName;

                    importantNotesCollection.setName(collectionName);
                    app.attach(&importantNotesCollection);
                }
                else {
                    std::cout << "The important notes collection already exist." << std::endl;
                }
                break;
            }

            case 3: {
                createCollections = false;
                break;
            }
            default: {
                break;
            }
        }
    }

    bool performOperations = true;

    while(performOperations) {
        std::cout << "Enter 1 to add a new note, 2 to remove a note, 3 to edit a note, 4 to block a note, 5 to unblock a note, 6 to exit : " << std::endl;
        int operationresult;
        std::cin >> operationresult;

        switch(operationresult) {
            case 1: {
                std::string collectionName, noteTitle, noteText;
                bool isImportant;

                std::cout << "Enter the collection name where you want to add the note : " << std::endl;
                std::cin >> collectionName;

                auto it = collections.find(collectionName);
            }

            default: {
                break;
            }
        }
    }
    return 0;
}