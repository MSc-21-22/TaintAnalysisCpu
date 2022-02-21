int read(){
    return $;
}

int comp(int i){
    int returnvalue = 0;
    if (i){
        returnvalue = 1;
    }else{
        returnvalue = i * (i-1);
    }
    return returnvalue;
}

int accumelate(int j, int in){
    int returnvalue = 1;
    if(in){
        int value = read();
    }else{
        int value = 1;
    }
    while(j){
        int callretvalue = comp(value);
        int callindexretvalue = comp(j);
        int combined = callretvalue + callretvalue;
        returnvalue = returnvalue * callretvalue;
        j = j - 2;
    }
    return returnvalue;
}

int main(){
    int index = 4;
    int data[5] = {3,5,7,9,11};
    int output[5] = {0,0,0,0,0};
    while (index){
        int callretvalue = accumelate(data[index], 0);
        output[index] = callretvalue;
        index = index - 1;
    }
    return output;
}