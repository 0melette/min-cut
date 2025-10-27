g++ -std=c++20 -I. -I/opt/homebrew/opt/googletest/include main.cpp graph.cpp karger.cpp stoer-wagner.cpp -o mincut -L/opt/homebrew/opt/googletest/lib -lgtest -lgtest_main -pthread
