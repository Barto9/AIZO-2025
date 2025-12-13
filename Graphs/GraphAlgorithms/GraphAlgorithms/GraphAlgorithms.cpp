
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>
#include "Timer.h"
#include "Graph.h"

void showHelp() {
    std::cout << "FILE TEST MODE:\n"
        << "    Usage:\n"
        << "        ./GraphAlgorithms --file <problem> <algorithm> <inputFile> [outputFile]\n"
        << "    <problem> Problem to solve (e.g. 0 - MST, 1 - shortest path)\n"
        << "    <algorithm> Algorithm for the problem\n"
        << "        For MST (e.g. 0 - all, 1 - Prim's, 2 - Kruskal's)\n"
        << "        For shortest (1 - Dijkstra)\n"
        << "    <inputFile> Input file containing the graf.\n"
        << "    [outputFile] If provided, solved problem will be stored there.\n\n"
        << "BENCHMARK MODE:\n"
        << "    Usage:\n"
        << "        ./GraphAlgorithms --test <problem> <algorithm> <size> <density> <count>\n"
        << "                <outputFile>\n"
        << "    <problem> Problem to solve (e.g. 0 - MST, 1 - shortest path)\n"
        << "    <algorithm> Algorithm for the problem\n"
        << "        For MST (e.g. 0 - all, 1 - Prim's, 2 - Kruskal's)\n"
        << "        For shortest (1 - Dijkstra)\n"
        << "    <size> Number of nodes.\n"
        << "    <density> Density of edges.\n"
        << "    <count> How many times test should be repeated (with graph regen).\n"
        << "    <outputFile> File where the benchmark results should be saved\n"
        << "        (every measured time is stored in seperate line).\n\n"
        << "HELP MODE:\n"
        << "    Usage:\n"
        << "        ./GraphAlgorithms --help\n"
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

        // Read file header to verify format
        std::ifstream verifyFile(inputFile);
        int declaredEdges, declaredVertices;
        if (!verifyFile.is_open()) {
            std::cerr << "Error: Could not open input file: " << inputFile << "\n";
            return 1;
        }
        
        // Read first line: edges and vertices (tab-separated)
        if (!(verifyFile >> declaredEdges >> declaredVertices)) {
            std::cerr << "Error: Invalid file format. First line must contain: edges<TAB>vertices\n";
            verifyFile.close();
            return 1;
        }
        verifyFile.close();

        std::cout << "\n=== File Format Verification ===\n";
        std::cout << "Declared in file: " << declaredEdges << " edges, " << declaredVertices << " vertices\n";

        // Load graph from file
        Graph graph;
        graph.loadFromFile(inputFile);
        
        // Verify loaded graph matches declared values
        int loadedEdges = graph.getSize();
        int loadedVertices = graph.getOrder();
        
        std::cout << "Loaded from structure: " << loadedEdges << " edges, " << loadedVertices << " vertices\n";
        
        if (loadedEdges != declaredEdges) {
            std::cerr << "WARNING: Number of edges mismatch! Declared: " << declaredEdges 
                      << ", Loaded: " << loadedEdges << "\n";
        } else {
            std::cout << "✓ Edge count verification: PASSED\n";
        }
        
        if (loadedVertices != declaredVertices) {
            std::cerr << "WARNING: Number of vertices mismatch! Declared: " << declaredVertices 
                      << ", Loaded: " << loadedVertices << "\n";
        } else {
            std::cout << "✓ Vertex count verification: PASSED\n";
        }
        
        // Initialize graph representations (matrix and list)
        bool directed = (problem == 1); // Shortest path uses directed graphs
        graph.init(directed);

        // Display graph in both representations
        std::cout << "\n=== Graph Representation ===\n";
        std::cout << "Graph type: " << (directed ? "Directed" : "Undirected") << "\n";
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
            std::cout << "\n=== Minimum Spanning Tree (MST) Solution ===\n";
            if (algorithm == 0) { // All MST algorithms
                std::cout << "\n--- Prim's Algorithm ---\n";
                timer.reset();
                timer.start();
                graph.mst_prim();
                timer.stop();
                std::cout << "Time elapsed: " << timer.result() << " ms\n";
                if (outFile.is_open()) {
                    outFile << "=== Prim's Algorithm ===\n";
                    outFile << "Time: " << timer.result() << " ms\n";
                }

                std::cout << "\n--- Kruskal's Algorithm ---\n";
                timer.reset();
                timer.start();
                graph.mst_kruskal();
                timer.stop();
                std::cout << "Time elapsed: " << timer.result() << " ms\n";
                if (outFile.is_open()) {
                    outFile << "\n=== Kruskal's Algorithm ===\n";
                    outFile << "Time: " << timer.result() << " ms\n";
                }
            }
            else if (algorithm == 1) { // Prim's
                std::cout << "\n--- Prim's Algorithm ---\n";
                timer.reset();
                timer.start();
                graph.mst_prim();
                timer.stop();
                std::cout << "Time elapsed: " << timer.result() << " ms\n";
                if (outFile.is_open()) {
                    outFile << "=== Prim's Algorithm ===\n";
                    outFile << "Time: " << timer.result() << " ms\n";
                }
            }
            else if (algorithm == 2) { // Kruskal's
                std::cout << "\n--- Kruskal's Algorithm ---\n";
                timer.reset();
                timer.start();
                graph.mst_kruskal();
                timer.stop();
                std::cout << "Time elapsed: " << timer.result() << " ms\n";
                if (outFile.is_open()) {
                    outFile << "=== Kruskal's Algorithm ===\n";
                    outFile << "Time: " << timer.result() << " ms\n";
                }
            }
            else {
                std::cerr << "Error: Invalid algorithm for MST. Use 0 (all), 1 (Prim's), or 2 (Kruskal's).\n";
                return 1;
            }
        }
        else if (problem == 1) { // Shortest path
            int startVertex
            int endVertex;
            cout << "Do you want to add start and end vertex? (y/n)";
            char answer;
            cin >> answer;
            if (answer == 'y') {
                cout << "Enter start vertex: ";
                cin >> startVertex;
                cout << "Enter end vertex: ";
                cin >> endVertex;
            }
            else {
            startVertex = 0;
            endVertex = (graph.getOrder() > 0) ? graph.getOrder() - 1 : 0;
            }
            std::cout << "\n=== Shortest Path Solution ===\n";
            std::cout << "Finding path from vertex " << startVertex << " to vertex " << endVertex << "\n";
            
            if (algorithm == 0) { // All shortest path algorithms
                std::cout << "\n--- Dijkstra's Algorithm ---\n";
                timer.reset();
                timer.start();
                graph.spp_dijkstra(startVertex, endVertex);
                timer.stop();
                std::cout << "Time elapsed: " << timer.result() << " ms\n";
                if (outFile.is_open()) {
                    outFile << "=== Dijkstra's Algorithm ===\n";
                    outFile << "From vertex " << startVertex << " to vertex " << endVertex << "\n";
                    outFile << "Time: " << timer.result() << " ms\n";
                }
            }
            else if (algorithm == 1) { // Dijkstra's
                std::cout << "\n--- Dijkstra's Algorithm ---\n";
                timer.reset();
                timer.start();
                graph.spp_dijkstra(startVertex, endVertex);
                timer.stop();
                std::cout << "Time elapsed: " << timer.result() << " ms\n";
                if (outFile.is_open()) {
                    outFile << "=== Dijkstra's Algorithm ===\n";
                    outFile << "From vertex " << startVertex << " to vertex " << endVertex << "\n";
                    outFile << "Time: " << timer.result() << " ms\n";
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

        if (problem != 0 && problem != 1) {
            std::cerr << "Error: Invalid problem type. Use 0 for MST, 1 for shortest path.\n";
            return 1;
        }

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

        // Uzywam tutaj vectorow do przechowywania czasow dla kazdego algorytmu i reprezentacji
        std::vector<double> primTimesMatrix;
        std::vector<double> primTimesList;
        std::vector<double> kruskalTimesMatrix;
        std::vector<double> kruskalTimesList;
        std::vector<double> dijkstraTimesMatrix;
        std::vector<double> dijkstraTimesList;

        for (int i = 0; i < count; i++) {
            Graph graph;
            graph.generateRandomGraph(size, density, directed);

            if (problem == 0) { // MST
                if (algorithm == 0 || algorithm == 1) { // Prim's
                    timer.reset();
                    timer.start();
                    graph.mst_prim_matrix();
                    timer.stop();
                    double resultMatrix = timer.result();
                    primTimesMatrix.push_back(resultMatrix);
                    outFile << "Prim_Matrix: " << resultMatrix << "\n";

                    timer.reset();
                    timer.start();
                    graph.mst_prim_list();
                    timer.stop();
                    double resultList = timer.result();
                    primTimesList.push_back(resultList);
                    outFile << "Prim_List: " << resultList << "\n";
                }
                if (algorithm == 0 || algorithm == 2) { // Kruskal's
                    timer.reset();
                    timer.start();
                    graph.mst_kruskal_matrix();
                    timer.stop();
                    double resultMatrix = timer.result();
                    kruskalTimesMatrix.push_back(resultMatrix);
                    outFile << "Kruskal_Matrix: " << resultMatrix << "\n";

                    timer.reset();
                    timer.start();
                    graph.mst_kruskal_list();
                    timer.stop();
                    double resultList = timer.result();
                    kruskalTimesList.push_back(resultList);
                    outFile << "Kruskal_List: " << resultList << "\n";
                }
            }
            else if (problem == 1) { // Shortest path
                int startVertex = 0;
                int endVertex = size - 1;
                if (algorithm == 0 || algorithm == 1) { // Dijkstra's
                    timer.reset();
                    timer.start();
                    graph.spp_dijkstra_matrix(startVertex, endVertex);
                    timer.stop();
                    double resultMatrix = timer.result();
                    dijkstraTimesMatrix.push_back(resultMatrix);
                    outFile << "Dijkstra_Matrix: " << resultMatrix << "\n";

                    timer.reset();
                    timer.start();
                    graph.spp_dijkstra_list(startVertex, endVertex);
                    timer.stop();
                    double resultList = timer.result();
                    dijkstraTimesList.push_back(resultList);
                    outFile << "Dijkstra_List: " << resultList << "\n";
                }
            }

            std::cout << "Completed test " << (i + 1) << "/" << count << "\n";
        }

        outFile << "\n=== STATISTICS ===\n";
        std::cout << "\n=== STATISTICS ===\n";

        // Helper function to calculate average
        auto calculateAverage = [](const std::vector<double>& times) -> double {
            if (times.empty()) return 0.0;
            double sum = 0.0;
            for (double t : times) {
                sum += t;
            }
            return sum / times.size();
        };

        // Helper function to calculate standard deviation
        auto calculateStdDev = [](const std::vector<double>& times, double avg) -> double {
            if (times.empty() || times.size() == 1) return 0.0;
            double sumSquaredDiff = 0.0;
            for (double t : times) {
                double diff = t - avg;
                sumSquaredDiff += diff * diff;
            }
            return std::sqrt(sumSquaredDiff / times.size());
        };

        // Print statistics for each algorithm and representation
        if (!primTimesMatrix.empty() || !primTimesList.empty()) {
            outFile << "Prim's Algorithm:\n";
            std::cout << "Prim's Algorithm:\n";
            
            if (!primTimesMatrix.empty()) {
                double primAvgMatrix = calculateAverage(primTimesMatrix);
                double primStdDevMatrix = calculateStdDev(primTimesMatrix, primAvgMatrix);
                outFile << "  Matrix Representation:\n";
                outFile << "    Average: " << std::fixed << std::setprecision(4) << primAvgMatrix << " ms\n";
                outFile << "    Std Dev: " << std::fixed << std::setprecision(4) << primStdDevMatrix << " ms\n";
                std::cout << "  Matrix Representation:\n";
                std::cout << "    Average: " << std::fixed << std::setprecision(4) << primAvgMatrix << " ms\n";
                std::cout << "    Std Dev: " << std::fixed << std::setprecision(4) << primStdDevMatrix << " ms\n";
            }
            
            if (!primTimesList.empty()) {
                double primAvgList = calculateAverage(primTimesList);
                double primStdDevList = calculateStdDev(primTimesList, primAvgList);
                outFile << "  List Representation:\n";
                outFile << "    Average: " << std::fixed << std::setprecision(4) << primAvgList << " ms\n";
                outFile << "    Std Dev: " << std::fixed << std::setprecision(4) << primStdDevList << " ms\n";
                std::cout << "  List Representation:\n";
                std::cout << "    Average: " << std::fixed << std::setprecision(4) << primAvgList << " ms\n";
                std::cout << "    Std Dev: " << std::fixed << std::setprecision(4) << primStdDevList << " ms\n";
            }
        }

        if (!kruskalTimesMatrix.empty() || !kruskalTimesList.empty()) {
            outFile << "Kruskal's Algorithm:\n";
            std::cout << "Kruskal's Algorithm:\n";
            
            if (!kruskalTimesMatrix.empty()) {
                double kruskalAvgMatrix = calculateAverage(kruskalTimesMatrix);
                double kruskalStdDevMatrix = calculateStdDev(kruskalTimesMatrix, kruskalAvgMatrix);
                outFile << "  Matrix Representation:\n";
                outFile << "    Average: " << std::fixed << std::setprecision(4) << kruskalAvgMatrix << " ms\n";
                outFile << "    Std Dev: " << std::fixed << std::setprecision(4) << kruskalStdDevMatrix << " ms\n";
                std::cout << "  Matrix Representation:\n";
                std::cout << "    Average: " << std::fixed << std::setprecision(4) << kruskalAvgMatrix << " ms\n";
                std::cout << "    Std Dev: " << std::fixed << std::setprecision(4) << kruskalStdDevMatrix << " ms\n";
            }
            
            if (!kruskalTimesList.empty()) {
                double kruskalAvgList = calculateAverage(kruskalTimesList);
                double kruskalStdDevList = calculateStdDev(kruskalTimesList, kruskalAvgList);
                outFile << "  List Representation:\n";
                outFile << "    Average: " << std::fixed << std::setprecision(4) << kruskalAvgList << " ms\n";
                outFile << "    Std Dev: " << std::fixed << std::setprecision(4) << kruskalStdDevList << " ms\n";
                std::cout << "  List Representation:\n";
                std::cout << "    Average: " << std::fixed << std::setprecision(4) << kruskalAvgList << " ms\n";
                std::cout << "    Std Dev: " << std::fixed << std::setprecision(4) << kruskalStdDevList << " ms\n";
            }
        }

        if (!dijkstraTimesMatrix.empty() || !dijkstraTimesList.empty()) {
            outFile << "Dijkstra's Algorithm:\n";
            std::cout << "Dijkstra's Algorithm:\n";
            
            if (!dijkstraTimesMatrix.empty()) {
                double dijkstraAvgMatrix = calculateAverage(dijkstraTimesMatrix);
                double dijkstraStdDevMatrix = calculateStdDev(dijkstraTimesMatrix, dijkstraAvgMatrix);
                outFile << "  Matrix Representation:\n";
                outFile << "    Average: " << std::fixed << std::setprecision(4) << dijkstraAvgMatrix << " ms\n";
                outFile << "    Std Dev: " << std::fixed << std::setprecision(4) << dijkstraStdDevMatrix << " ms\n";
                std::cout << "  Matrix Representation:\n";
                std::cout << "    Average: " << std::fixed << std::setprecision(4) << dijkstraAvgMatrix << " ms\n";
                std::cout << "    Std Dev: " << std::fixed << std::setprecision(4) << dijkstraStdDevMatrix << " ms\n";
            }
            
            if (!dijkstraTimesList.empty()) {
                double dijkstraAvgList = calculateAverage(dijkstraTimesList);
                double dijkstraStdDevList = calculateStdDev(dijkstraTimesList, dijkstraAvgList);
                outFile << "  List Representation:\n";
                outFile << "    Average: " << std::fixed << std::setprecision(4) << dijkstraAvgList << " ms\n";
                outFile << "    Std Dev: " << std::fixed << std::setprecision(4) << dijkstraStdDevList << " ms\n";
                std::cout << "  List Representation:\n";
                std::cout << "    Average: " << std::fixed << std::setprecision(4) << dijkstraAvgList << " ms\n";
                std::cout << "    Std Dev: " << std::fixed << std::setprecision(4) << dijkstraStdDevList << " ms\n";
            }
        }

        outFile.close();
        std::cout << "\nBenchmark complete. Results saved to: " << outputFile << "\n";
    }
    else {
        std::cerr << "Error: Invalid mode. Use --file, --test, or --help.\n";
        showHelp();
        return 1;
    }

    return 0;
}

