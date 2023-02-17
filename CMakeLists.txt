cmake_minimum_required(VERSION 3.5)

project(combin LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(kkSolvers KnapsackSolvers.cpp kpSolver.cpp kpSolverDP.cpp kpSolverGreedy.cpp kpSolverHeurDP.cpp)
add_executable(testProgDyn testProgDyn.cpp kpSolver.cpp kpSolverDP.cpp kpSolverGreedy.cpp kpSolverHeurDP.cpp)
add_executable(testHeur testHeur.cpp kpSolver.cpp kpSolverDP.cpp kpSolverGreedy.cpp kpSolverHeurDP.cpp)
add_executable(testBB testBB.cpp  kpSolver.cpp kpSolverDP.cpp  kpSolverGreedy.cpp kpSolverHeurDP.cpp nodeBB.cpp kpSolverBB.cpp)
