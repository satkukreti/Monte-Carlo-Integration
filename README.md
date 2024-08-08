# Monte Carlo Integration

The goal was to solve the definite integral`∫(a to b) (sin(x)/x) dx`. I used Monte Carlo integration to estimate the answer within user-inputted bounds. I also used C++ threads (because it's much simpler than using pthreads :) ) to speed up the process.

My answers are within 5-6 decimal points of Wolfram Alpha's result.

## How to Run My Code

1. Compile the code:
    ```bash
    make
    ```

2. Run the compiled program:
    ```bash
    ./integrate a b n n_threads
    ```
