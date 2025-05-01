#pragma once

union Color
{
    struct
    {
        int r;
        int g;
        int b;
        int a;
    };
    int x;
    int y;
    int z;
    int w;
};
