#include <vector>
#include <ctime>
#include <iostream>
#include <benchmark/benchmark.h>
#include "openexr/half.h"
#define TINYEXR_IMPLEMENTATION 1
#include "../tinyexr.h" 
using namespace std;
using namespace tinyexr;

inline float rand_float() {
  // TODO: get random number distribution close to openexr images 
  // this one is just for quick testing
  int r = rand(); // not full range: RAND_MAX == unsigned int max / 2
  return *reinterpret_cast<float*>(&r);
}

static void BM_HalfConversionOpenEXR(benchmark::State& state) {
  for (auto _ : state){
        state.PauseTiming();
        srand(time(nullptr));
        half h;
        float f = rand_float();
        state.ResumeTiming();
        benchmark::DoNotOptimize(h = half(f));
  }

}
BENCHMARK(BM_HalfConversionOpenEXR);

static void BM_HalfConversionTinyEXR(benchmark::State& state) {
  for (auto _ : state){
        state.PauseTiming();
        srand(time(nullptr));
        FP32 fp32 = {0};
        FP16 fp16;
        fp32.f = rand_float();
        state.ResumeTiming();
        benchmark::DoNotOptimize(fp16 = float_to_half_full(fp32));  
  }

}
BENCHMARK(BM_HalfConversionTinyEXR);

BENCHMARK_MAIN();


