#ifndef RESULT_H
#define RESULT_H

enum Result
{
    Success = 0,
    InvaildAlgorithmName = 1,
    InvalidOptionName = 3,

    FaildtoUpdatePath = 5,

    InvaildParameter = 50, // error: Number of parameters

    CommandFileNotExist = 100,
    LoadFileNotExist,

    VertexKeyNotExist = 200,
    InvalidVertexKey,
    GraphNotExist,
    InvalidAlgorithm,
    NegativeCycleDetected,
    IsolatedVertex, //error: can't visit endvertex

    NonDefinedCommand = 300,
};

#endif
