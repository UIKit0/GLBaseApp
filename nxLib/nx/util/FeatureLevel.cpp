#include "stdafx.h"
#include "nx/nxLib.h"
#include "nx/util/FeatureLevel.h"

const D3D10_FEATURE_LEVEL1 levelAttemptsForDX10[] = {
    D3D10_FEATURE_LEVEL_10_1,
    D3D10_FEATURE_LEVEL_10_0,
    D3D10_FEATURE_LEVEL_9_3,
    D3D10_FEATURE_LEVEL_9_2,
    D3D10_FEATURE_LEVEL_9_1,
};
const wchar_t *levelLabelsForDX10[] = {
    L"D3D10_FEATURE_LEVEL_10_1",
    L"D3D10_FEATURE_LEVEL_10_0",
    L"D3D10_FEATURE_LEVEL_9_3",
    L"D3D10_FEATURE_LEVEL_9_2",
    L"D3D10_FEATURE_LEVEL_9_1",
};

const D3D_FEATURE_LEVEL levelAttemptsForDX11[] = {
    D3D_FEATURE_LEVEL_11_0,
    D3D_FEATURE_LEVEL_10_1,
    D3D_FEATURE_LEVEL_10_0,
    D3D_FEATURE_LEVEL_9_3,
    D3D_FEATURE_LEVEL_9_2,
    D3D_FEATURE_LEVEL_9_1,
};
const wchar_t *levelLabelsForDX11[] = {
    L"D3D_FEATURE_LEVEL_11_0",
    L"D3D_FEATURE_LEVEL_10_1",
    L"D3D_FEATURE_LEVEL_10_0",
    L"D3D_FEATURE_LEVEL_9_3",
    L"D3D_FEATURE_LEVEL_9_2",
    L"D3D_FEATURE_LEVEL_9_1",
};

nx::util::FeatureLevel::FeatureLevel( D3D_FEATURE_LEVEL minimulLevel /*= D3D_FEATURE_LEVEL_10_0*/ )
{
    minimumFeatureLevel = 0;
    for (UINT i = 0; i < sizeof(levelAttemptsForDX11); ++i) {
        if (levelAttemptsForDX11[i] == minimulLevel) {
            minimumFeatureLevel = i;
            break;
        }
    }
    if (minimumFeatureLevel == 0) {
        throw std::invalid_argument("Unknown feature level");
    }

    for (UINT i = 0; i < ARRAYSIZE(levelAttemptsForDX10); ++i) {
        m_featureLevelLabelsForDX10.insert(
            std::make_pair<D3D10_FEATURE_LEVEL1, std::wstring>(levelAttemptsForDX10[i], levelLabelsForDX10[i]));
    }
    for (UINT i = 0; i < ARRAYSIZE(levelAttemptsForDX11); ++i) {
        m_featureLevelLabelsForDX11.insert(
            std::make_pair<D3D_FEATURE_LEVEL, std::wstring>(levelAttemptsForDX11[i], levelLabelsForDX11[i]));
    }
}

D3D_FEATURE_LEVEL nx::util::FeatureLevel::GetFeatureLevelForDX11( UINT index ) const
{
    if (index < GetNumberOfFeatureLevelsForDX11()) {
        return levelAttemptsForDX11[index];
    } else {
        throw std::out_of_range("index is out of range");
    }
}

const D3D_FEATURE_LEVEL* nx::util::FeatureLevel::GetFeatureLevelsForDX11() const
{
    return levelAttemptsForDX11;
}

D3D10_FEATURE_LEVEL1 nx::util::FeatureLevel::GetFeatureLevelForDX10( UINT index ) const
{
    if (index <= GetNumberOfFeatureLevelsForDX10()) {
        return levelAttemptsForDX10[index];
    } else {
        throw std::out_of_range("index is out of range");
    }
}

const D3D10_FEATURE_LEVEL1* nx::util::FeatureLevel::GetFeatureLevelsForDX10() const
{
    return levelAttemptsForDX10;
}

