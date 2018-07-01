#include <vector>
#include <immintrin.h>
#include <emmintrin.h>
#include <ctime>
#include <iostream>
#include <benchmark/benchmark.h>
#include "openexr/half.h"
#define TINYEXR_IMPLEMENTATION 1
#include "../tinyexr.h" 

using namespace std;
using namespace tinyexr;

static const size_t buffer_size = 2048;
static vector<float> float_vec(buffer_size);

inline float rand_float() {
  // TODO: get random number distribution close to openexr images 
  // this one is just for quick testing
  int r = rand(); // not full range: RAND_MAX == unsigned int max / 2
  return *reinterpret_cast<float*>(&r);
}

extern unsigned short float_to_half(float f);
static FP16 float_to_half_test(FP32 f) {
    FP16 o = {0};
    o.u = float_to_half(f.f);  
    return o;
}

static void BM_HalfConversionOpenEXR(benchmark::State& state) {
  half h = 0;
  for (auto _ : state){
        float f = float_vec[state.iterations() % buffer_size]; 
        h = half(f);
        benchmark::DoNotOptimize(h);
        benchmark::DoNotOptimize(f);
  }

}
BENCHMARK(BM_HalfConversionOpenEXR);

static void BM_HalfConversionTinyEXR(benchmark::State& state) {
  FP32 fp32 = {0};
  FP16 fp16;
  for (auto _ : state){
        fp32.f = float_vec[state.iterations() % buffer_size];
        fp16 = float_to_half_full(fp32);
  }
  benchmark::DoNotOptimize(fp32);  
  benchmark::DoNotOptimize(fp16);  

}
BENCHMARK(BM_HalfConversionTinyEXR);

static void BM_HalfConversionTest(benchmark::State& state) {
  FP32 fp32 = {0};
  FP16 fp16;
  for (auto _ : state){
        fp32.f = float_vec[state.iterations() % buffer_size];
        fp16 = float_to_half_test(fp32);
  }
//  benchmark::DoNotOptimize(fp32);  
//  benchmark::DoNotOptimize(fp16);  
}
BENCHMARK(BM_HalfConversionTest);
//BENCHMARK_MAIN();

int main(int argc, char** argv) {
  srand(time(nullptr));
  for (auto &val : float_vec){
     val = rand_float(); 
  }
  benchmark::Initialize(&argc, argv);
  benchmark::RunSpecifiedBenchmarks();
}


