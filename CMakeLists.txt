cmake_minimum_required(VERSION 2.8.4)
project(jhelper-example-project)

file(GLOB TASKS "tasks/*.cpp")
file(GLOB_RECURSE HEADERS "library/*.h" )
add_executable(output output/main.cpp ${HEADERS} library/MinSegmentTree.h library/SumFenwickTree.h library/Bridges.h library/StronglyConnectedComponents.h library/MinimumSpanningTree.h library/Dijkstra.h library/MaxFlow.h library/MaxBipartiteMatching.h library/PrimeSieve.h library/SuffixArray.h library/Geometry2D.h library/FFT.h library/ModLong.h library/HungarianMethod.h library/Random.h library/RangeSumSegmentTree.h library/Fraction.h)
add_executable(testrunner testrunner/main.cpp ${HEADERS} library/MinSegmentTree.h library/SumFenwickTree.h library/Bridges.h library/StronglyConnectedComponents.h library/MinimumSpanningTree.h library/Dijkstra.h library/MaxFlow.h library/MaxBipartiteMatching.h library/PrimeSieve.h library/SuffixArray.h library/Geometry2D.h library/FFT.h library/ModLong.h library/HungarianMethod.h library/Random.h library/RangeSumSegmentTree.h)

ADD_DEFINITIONS(-std=c++17)
ADD_DEFINITIONS(-O3)

#add_executable(test ${TASKS} ${HEADERS} library/MinSegmentTree.h library/SumFenwickTree.h snippets/FloodFill.cpp snippets/DfsBfs.cpp snippets/TopSort.cpp library/Bridges.h)