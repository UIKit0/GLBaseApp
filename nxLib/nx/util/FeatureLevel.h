#ifndef NX_UTIL_FEATURELEVEL_H_
#define NX_UTIL_FEATURELEVEL_H_

namespace nx
{
namespace util
{
class FeatureLevel
{
private:
    std::map<D3D_FEATURE_LEVEL, std::wstring> m_featureLevelLabelsForDX11;
    std::map<D3D10_FEATURE_LEVEL1, std::wstring> m_featureLevelLabelsForDX10;
    UINT minimumFeatureLevel;
public:
    FeatureLevel(D3D_FEATURE_LEVEL minimulLevel = D3D_FEATURE_LEVEL_10_0);
    virtual ~FeatureLevel() {}

    UINT GetNumberOfFeatureLevelsForDX10() const {
        return minimumFeatureLevel;
    }
    D3D10_FEATURE_LEVEL1 GetFeatureLevelForDX10(UINT index) const;
    const D3D10_FEATURE_LEVEL1* GetFeatureLevelsForDX10() const;
    const std::wstring& GetFeatureLevelLabel(D3D10_FEATURE_LEVEL1 level) const {
        return m_featureLevelLabelsForDX10.at(level);
    }

    UINT GetNumberOfFeatureLevelsForDX11() const {
        return minimumFeatureLevel + 1;
    }
    D3D_FEATURE_LEVEL GetFeatureLevelForDX11(UINT index) const;
    const D3D_FEATURE_LEVEL* GetFeatureLevelsForDX11() const;
    const std::wstring& GetFeatureLevelLabel(D3D_FEATURE_LEVEL level) const {
        return m_featureLevelLabelsForDX11.at(level);
    }
};
}
}


#endif // NX_UTIL_FEATURELEVEL_H_