enum KernelResult {
    Success,
    Failure
};

enum KernelResult add_with_cuda(int* out, const int *a, const int *b, int width, int height);