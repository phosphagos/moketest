#pragma once
#include "moke/tensor/tensor.hpp"
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <moke/kernels.hpp>
#include <moketest/executor.hpp>

using namespace moke;
using namespace moketest;
class ColorToGrayscaleExecutor : public Executor<ColorToGrayscaleExecutor> {
private:
    size_t width, height;
    HostTensor<uint8_t, 3> hbuf_in;
    DeviceTensor<uint8_t, 3> dbuf_in;
    HostTensor<uint8_t, 2>  hbuf_out, base_out;
    DeviceTensor<uint8_t, 2> dbuf_out;

public:
    ColorToGrayscaleExecutor(size_t width, size_t height, int warm_loop = 100, int perf_loop = 300)
            : Executor<ColorToGrayscaleExecutor>{warm_loop, perf_loop},
              width{width}, height{height}, hbuf_in{height, width, 3u}, dbuf_in{height, width, 3u},
              hbuf_out{height, width}, dbuf_out{height, width}, base_out{height, width} {}

    void init_input() {
        HostRandomGenerator generator;
        generator.fill(hbuf_in);
    }

    void load() {
        dbuf_in.load(hbuf_in);
    }

    void store() {
        dbuf_out.store(hbuf_out);
    }

    void compute() {
        ColorToGrayscale(dbuf_in, dbuf_out);
    }

    void compute_baseline() {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                auto r = hbuf_in[i][j][0];
                auto g = hbuf_in[i][j][1];
                auto b = hbuf_in[i][j][2];
                base_out[i][j] = 0.21f * r + 0.71f * g + 0.07f * b;
            }
        }
    }

    bool compare_accuracy() {
        RelativeErrorComparator comp{};
        auto result = comp(hbuf_out.data(), base_out.data(), hbuf_out.size());
        result.print();
        return bool(result);
    }

    size_t theoretical_ops() {
        return dbuf_out.size() * 3;
    }

    size_t theoretical_iobytes() {
        return dbuf_in.bytes() + dbuf_out.bytes();
    }
};
