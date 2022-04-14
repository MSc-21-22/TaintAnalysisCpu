int g(int n){
    int out = 0;
    if(n){
        out = 5;
    }else{
        out = n;
    }
    return n;
}

int f(int a){
    int n = a;
    int j = g(n);
    int x = g(j);

    return x;
}

void main(int j){
    int a = f($);
    [f]{int a = f(a)};
}