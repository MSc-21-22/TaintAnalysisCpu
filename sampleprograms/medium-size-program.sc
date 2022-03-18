int read(){
    return $;
}

int detour(int baba){
    int is = read();
    int you = 0;

    if(baba + is + you){
        baba = 5;
    }else{
        you = baba + is;
    }

    while(baba){
        baba = baba + baba;
    }
    return baba;
}

int takingmanyparams(int a, int b, int c, int d, int e){
    int value = 0;
    if(a){
        if(b){
            if(c){
                if(d){
                    value = 4+d;
                }else{
                    value = 3+c;
                }
            }else{
                value = 2+b;
            }
        }else{
            value = 1+a;
        }
    }else{
        value = 0;
    }
    int value = detour(a+b+c);
    int value1 = detour(d+e);
    int something = 0;
    int comb = 0;
    if(value){
        something = something + value;
        something = e;
        something = d;
        something = c;
        something = b;
        something = a;
    }else{
        comb = a+b;
        comb = b+c;
        comb = c+d;
        comb = d+e;
    }
    int iffer = 0;

    if(a+b+c+d+e){
        if(c+d){
            iffer = c+d;
        }else{
            iffer = a+b+e;
        }
    }else{
        if(b+e){
            iffer = b+e;
        }else{
            iffer = a+c+d;
        }
    }
    int er = a+b+c+d+e;
    return er;
}

int paramtester(){
    int t = read();
    int value1 = takingmanyparams(t, 2, 3, 4, 5);
    int value2 = takingmanyparams(1, t, 3, 4, 5);
    int value3 = takingmanyparams(1, 2, t, 4, 5);
    int value4 = takingmanyparams(1, 2, 3, t, 5);
    int value5 = takingmanyparams(1, 2, 3, 4, t);
    int value0 = takingmanyparams(1, 2, 3, 4, 5);
    return value0;
}

int main(){
    int value = paramtester();
    while(value){
        value = value-1;
    }
    if(value){
        int wat = read();
    }else{
        int wat = value;
    }

    int rut = detour(wat);
    return wat;
}