#include <bits/stdc++.h>

int main() {

    for (int i = 0; i < 16; i++) {
        /*
        printf("Mux(a = a[%d], b = b[%d], sel = sel[0], out = out0%d);\n\\
        Mux(a = c[%d], b = d[%d], sel = sel[0], out = out1%d);\n\\
        Mux(a = out0%d, b = out1%d, sel = sel[1], out = out[%d]);\n\n", i, i, i, i, i, i, i, i, i);
        */

        /*
        printf("Mux(a = a[%d], b = b[%d], sel = sel[0], out = out00d%d);\n", i, i, i);
        printf("Mux(a = c[%d], b = d[%d], sel = sel[0], out = out01d%d);\n", i, i, i);
        printf("Mux(a = e[%d], b = f[%d], sel = sel[0], out = out10d%d);\n", i, i, i);
        printf("Mux(a = g[%d], b = h[%d], sel = sel[0], out = out11d%d);\n", i, i, i);
        puts("");
        printf("Mux(a = out00d%d, b = out01d%d, sel = sel[1], out = out0d%d);\n", i, i, i);
        printf("Mux(a = out10d%d, b = out11d%d, sel = sel[1], out = out1d%d);\n", i, i, i);
        puts("");
        printf("Mux(a = out0d%d, b = out1d%d, sel = sel[2], out = out[%d]);\n", i, i, i);
        puts("");
        */
        //printf("Mux(a = a[%d], b = b[%d], sel = sel, out = out[%d]);\n", i, i, i);
        printf("FullAdder(a = a[%d], b = b[%d], c = carry%d, sum = out[%d], carry = carry%d);\n", i, i, i - 1, i, i);
    }

    return 0;
}