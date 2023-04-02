void funcao1()
{
while (true)
{
get(A);
get(B);
get(C);
// critical
region:
// use A, B, C
release(A);
release(B);
release(C);
}
}

void funcao2()
{
while (true)
{
get(D);
get(E);
get(B);
// critical
region:
// use D, E, B
release(D);
release(E);
release(B);
}
}

void funcao3()
{
while (true)
{
get(C);
get(F);
get(D);
// critical
region:
// use C, F, D
release(C);
release(F);
release(D);
}
}