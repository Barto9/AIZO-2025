#include <iostream>
#include <string>
#include <fstream>
#include "Timer.h"
#include "Graph.h"

void showHelp() {
    std::cout << "FILE TEST MODE:\n"
        << "    Usage:\n"
        << "        ./YourProject --file <problem> <algorithm> <inputFile> [outputFile]\n"
        << "    <problem> Problem to solve (e.g. 0 - MST, 1 - shortest path)\n"
        << "    <algorithm> Algorithm for the problem\n"
        << "        For MST (e.g. 0 - all, 1 - Prim's, ...)\n"
        << "        For shortest (e.g. 0 - all, 1 - Dijkstra, ...)\n"
        << "    <inputFile> Input file containing the graf.\n"
        << "    [outputFile] If provided, solved problem will be stored there.\n\n"
        << "BENCHMARK MODE:\n"
        << "    Usage:\n"
        << "        ./YourProject --test <problem> <algorithm> <size> <density> <count>\n"
        << "                <outputFile>\n"
        << "    <problem> Problem to solve (e.g. 0 - MST, 1 - shortest path)\n"
        << "    <algorithm> Algorithm for the problem\n"
        << "        For MST (e.g. 0 - all, 1 - Prim's, ...)\n"
        << "        For shortest (e.g. 0 - all, 1 - Dijkstra, ...)\n"
        << "    <size> Number of nodes.\n"
        << "    <density> Density of edges.\n"
        << "    <count> How many times test should be repeated (with graph regen).\n"
        << "    <outputFile> File where the benchmark results should be saved\n"
        << "        (every measured time is stored in seperate line).\n\n"
        << "HELP MODE:\n"
        << "    Usage:\n"
        << "        ./YourProject --help\n"
        << "    Displays this help message.\n"
        << "    Notes:\n"
        << "    - The help message will also appear if no arguments are provided.\n"
        << "    - Ensure that either --file or --test mode is specified;\n"
        << "        they are mutually exclusive.\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2 || std::string(argv[1]) == "--help") {
        showHelp();
        return 0;
    }

    std::string mode = argv[1];

    // FILE TEST MODE
    if (mode == "--file") {
        if (argc < 5) {
            std::cerr << "Error: Insufficient arguments for --file mode.\n";
            showHelp();
            return 1;
        }

        int problem = std::stoi(argv[2]);
        int algorithm = std::stoi(argv[3]);
        std::string inputFile = argv[4];
        std::string outputFile = (argc >= 6) ? argv[5] : "";

        // Validate problem type
        if (problem != 0 && problem != 1) {
            std::cerr << "Error: Invalid problem type. Use 0 for MST, 1 for shortest path.\n";
            return 1;
        }

        // Load graph from file
        Graph graph;
        graph.loadFromFile(inputFile);
        // Initialize graph representations (matrix and list)
        // Determine if graph is directed based on problem type
        bool directed = (problem == 1); // Shortest path uses directed graphs
        graph.init(directed);

        // Display graph
        std::cout << "Loaded graph:\n";
        graph.display();

        Timer timer;
        std::ofstream outFile;

        if (!outputFile.empty()) {
            outFile.open(outputFile);
            if (!outFile.is_open()) {
                std::cerr << "Error: Failed to open output file: " << outputFile << "\n";
                return 1;
            }
        }

        // Execute algorithm based on problem type
        if (problem == 0) { // MST
            if (algorithm == 0) { // All MST algorithms
                std::cout << "\n=== Running Prim's algorithm ===\n";
                timer.reset();
                timer.start();
                graph.mst_prim();
                timer.stop();
                std::cout << "Time elapsed: " << timer.result() << " ms\n";
                if (outFile.is_open()) {
                    outFile << "Prim: " << timer.result() << " ms\n";
                }

                std::cout << "\n=== Running Kruskal's algorithm ===\n";
                timer.reset();
                timer.start();
                graph.mst_kruskal();
                timer.stop();
                std::cout << "Time elapsed: " << timer.result() << " ms\n";
                if (outFile.is_open()) {
                    outFile << "Kruskal: " << timer.result() << " ms\n";
                }
            }
            else if (algorithm == 1) { // Prim's
                std::cout << "\n=== Running Prim's algorithm ===\n";
                timer.reset();
                timer.start();
                graph.mst_prim();
                timer.stop();
                std::cout << "Time elapsed: " << timer.result() << " ms\n";
                if (outFile.is_open()) {
                    outFile << timer.result() << "\n";
                }
            }
            else if (algorithm == 2) { // Kruskal's
                std::cout << "\n=== Running Kruskal's algorithm ===\n";
                timer.reset();
                timer.start();
                graph.mst_kruskal();
                timer.stop();
                std::cout << "Time elapsed: " << timer.result() << " ms\n";
                if (outFile.is_open()) {
                    outFile << timer.result() << "\n";
                }
            }
            else {
                std::cerr << "Error: Invalid algorithm for MST. Use 0 (all), 1 (Prim's), or 2 (Kruskal's).\n";
                return 1;
            }
        }
        else if (problem == 1) { // Shortest path
            // For shortest path, read order from file to determine end vertex
            // Read first line to get order (number of vertices)
            std::ifstream tempFile(inputFile);
            int tempSize, tempOrder;
            if (tempFile.is_open()) {
                tempFile >> tempSize >> tempOrder;
                tempFile.close();
            }
            else {
                std::cerr << "Error: Could not read graph order from file.\n";
                return 1;
            }
            
            int startVertex = 0;
            int endVertex = (tempOrder > 0) ? tempOrder - 1 : 0;

            if (algorithm == 0) { // All shortest path algorithms
                std::cout << "\n=== Running Dijkstra's algorithm ===\n";
                std::cout << "From vertex " << startVertex << " to vertex " << endVertex << "\n";
                timer.reset();
                timer.start();
                graph.spp_dijkstra(startVertex, endVertex);
                timer.stop();
                std::cout << "Time elapsed: " << timer.result() << " ms\n";
                if (outFile.is_open()) {
                    outFile << "Dijkstra: " << timer.result() << " ms\n";
                }
            }
            else if (algorithm == 1) { // Dijkstra's
                std::cout << "\n=== Running Dijkstra's algorithm ===\n";
                std::cout << "From vertex " << startVertex << " to vertex " << endVertex << "\n";
                timer.reset();
                timer.start();
                graph.spp_dijkstra(startVertex, endVertex);
                timer.stop();
                std::cout << "Time elapsed: " << timer.result() << " ms\n";
                if (outFile.is_open()) {
                    outFile << timer.result() << "\n";
                }
            }
            else {
                std::cerr << "Error: Invalid algorithm for shortest path. Use 0 (all) or 1 (Dijkstra).\n";
                return 1;
            }
        }

        if (outFile.is_open()) {
            outFile.close();
            std::cout << "\nResults saved to: " << outputFile << "\n";
        }
    }
    // BENCHMARK MODE
    else if (mode == "--test") {
        if (argc < 8) {
            std::cerr << "Error: Insufficient arguments for --test mode.\n";
            showHelp();
            return 1;
        }

        int problem = std::stoi(argv[2]);
        int algorithm = std::stoi(argv[3]);
        int size = std::stoi(argv[4]);
        int density = std::stoi(argv[5]);
        int count = std::stoi(argv[6]);
        std::string outputFile = argv[7];

        // Validate problem type
        if (problem != 0 && problem != 1) {
            std::cerr << "Error: Invalid problem type. Use 0 for MST, 1 for shortest path.\n";
            return 1;
        }

        // Open output file
        std::ofstream outFile(outputFile);
        if (!outFile.is_open()) {
            std::cerr << "Error: Failed to open output file: " << outputFile << "\n";
            return 1;
        }

        std::cout << "Running benchmark: problem=" << problem 
                  << ", algorithm=" << algorithm 
                  << ", size=" << size 
                  << ", density=" << density 
                  << ", count=" << count << "\n";

        Timer timer;
        bool directed = (problem == 1); // Shortest path uses directed graphs

        for (int i = 0; i < count; i++) {
            Graph graph;
            graph.generateRandomGraph(size, density, directed);

            if (problem == 0) { // MST
                if (algorithm == 0 || algorithm == 1) { // Prim's
                    timer.reset();
                    timer.start();
                    graph.mst_prim();
                    timer.stop();
                    outFile << timer.result() << "\n";
                }
                if (algorithm == 0 || algorithm == 2) { // Kruskal's
                    timer.reset();
                    timer.start();
                    graph.mst_kruskal();
                    timer.stop();
                    outFile << timer.result() << "\n";
                }
            }
            else if (problem == 1) { // Shortest path
                int startVertex = 0;
                int endVertex = size - 1;
                if (algorithm == 0 || algorithm == 1) { // Dijkstra's
                    timer.reset();
                    timer.start();
                    graph.spp_dijkstra(startVertex, endVertex);
                    timer.stop();
                    outFile << timer.result() << "\n";
                }
            }

            std::cout << "Completed test " << (i + 1) << "/" << count << "\n";
        }

        outFile.close();
        std::cout << "Benchmark complete. Results saved to: " << outputFile << "\n";
    }
    else {
        std::cerr << "Error: Invalid mode. Use --file, --test, or --help.\n";
        showHelp();
        return 1;
    }

    return 0;
}

