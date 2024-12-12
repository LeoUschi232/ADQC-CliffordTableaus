#pragma once

namespace CliffordTableaus {
    class QuArray {
    public:
        QuArray(int n);

        ~QuArray();

        void set(int i, int j, int val);

        int get(int i, int j);

        void print();

    private:
        int n;
        int *data;
    };
}

