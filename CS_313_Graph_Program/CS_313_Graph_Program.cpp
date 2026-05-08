#include <iostream>
#include <fstream>
#include <string>
#include "Menufunctions.h"
#include "EdgeClasses.h"
#include "VertexClasses.h"

//note: open and close file here, as well as verifying. Just pass the open ifstream to the function by reference. Same applies to graph 2.
int main()
{
    int choice;
    std::string choiceStr;
    std::string fileName;
    EdgeTree* graphRoot = NULL;

    do
    {
        std::cout << "Welcome to the Graph Checker! Please select an option:\n"
            << "1: Load Graph File\n"
            << "2: Search for Edge\n"
            << "3: Print Graph\n"
            << "4: Compare Against Another Graph\n"
            << "5: Exit\n\nYour choice: ";
        std::getline(std::cin, choiceStr);
        choice = std::stoi(choiceStr);
        while (choice < 1 || choice > 5)
        {
            std::cout << "Please enter a valid number: ";
            std::getline(std::cin, choiceStr);
            choice = std::stoi(choiceStr);
        }

        if (choice == 1)
        {
            std::ifstream graphFile;
            std::cout << "\n----------\nPlease enter a file to load (default: graph.txt): ";
            std::getline(std::cin, fileName);
            if (fileName == "")
            {
                fileName = "graph.txt";
            }

            graphFile.open(fileName);
            while (!graphFile.is_open())
            {
                std::cout << "That file does not exist. Please check the folder or enter a new file name: ";
                std::getline(std::cin, fileName);
                if (fileName == "")
                {
                    fileName = "graph.txt";
                }
                graphFile.open(fileName);
            }

            fillGraph(graphRoot, graphFile);

            graphFile.close();
            std::cout << "\nLoaded!\n----------\n";
        }
        else if (choice == 2 && graphRoot != NULL)
        {
            double x1;
            double y1;
            double x2;
            double y2;
            std::string numHolder;
            
            std::cout << "\n----------\nPlease enter the X coordinate of the first point: ";
            std::getline(std::cin, numHolder);
            x1 = std::stod(numHolder);
            std::cout << "Please enter the Y coordinate of the first point: ";
            std::getline(std::cin, numHolder);
            y1 = std::stod(numHolder);
            std::cout << "Please enter the X coordinate of the second point: ";
            std::getline(std::cin, numHolder);
            x2 = std::stod(numHolder);
            std::cout << "Please enter the Y coordinate of the second point: ";
            std::getline(std::cin, numHolder);
            y2 = std::stod(numHolder);
            
            EdgeTree target(x1, y1, x2, y2);

            bool success = edgeExists(graphRoot, target);

            if (success == true)
            {
                std::cout << "\nThat edge exists in this graph!\n----------\n";
            }
            else
            {
                std::cout << "\nThat edge does not exist in this graph. If you think this may be an error, \ntry swapping the order you enter the two points.\n----------\n";
            }
        }
        else if (choice == 3 && graphRoot != NULL)
        {
            std::cout << "\n----------\n";
            printGraph(graphRoot);
            std::cout << "\n----------\n";
        }
        else if (choice == 4 && graphRoot != NULL)
        {
            std::string newFileName;
            std::ifstream graphFile;
            std::cout << "\n----------\nPlease enter a file to load: ";
            std::getline(std::cin, newFileName);
            if (fileName == newFileName)
            {
                std::cout << "Please enter a different file from the first graph: ";
            }

            graphFile.open(newFileName);
            while (!graphFile.is_open())
            {
                std::cout << "That file does not exist. \nPlease check the folder or enter a new file name: ";
                std::getline(std::cin, newFileName);
                if (fileName == newFileName)
                {
                    std::cout << "Please enter a different file from the first graph: ";
                }
                graphFile.open(newFileName);
            }

            bool intersects = compareGraphs(graphRoot, graphFile);

            graphFile.close();

            if (intersects == true)
            {
                std::cout << "\nThese graphs intersect!\n-----------\n";
            }
            else
            {
                std::cout << "\nThese graphs do not intersect.\n----------\n";
            }
        }
        else if (choice == 5)
        {

            clearEdgeTree(graphRoot);
            std::cout << "\nGoodbye!";
        }
        //choice is not 1 or 5, but the graph is empty
        else
        {
            std::cout << "\nGraph is empty! Please load a graph first (Option 1).\n----------\n";
        }
    } while (choice != 5);
}
