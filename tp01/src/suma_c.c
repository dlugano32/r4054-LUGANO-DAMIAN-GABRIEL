
int suma_c (int, int);

__attribute__((section(".text"))) int suma_c(int a, int b)      // le decimos en que seccion va a estar 
    {
        int c;

        c = a + b;

        return c;
    }