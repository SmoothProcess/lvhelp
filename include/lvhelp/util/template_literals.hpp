#ifndef LVHELP_TEMPLATE_LITERALS
#define LVHELP_TEMPLATE_LITERALS

namespace lvhelp{

template<size_t N>
struct StringLiteral{
	constexpr StringLiteral(const char (&str)[N]){
		std::copy_n(str, N, value);
	}

	char value[N];
};

#define TEMPLATE_STR StringLiteral

struct TemplateDouble{
	double value;
	constexpr TemplateDouble(const double val) : value(val){}
	constexpr TemplateDouble(const float val) : value(val){}
};

} // lvhelp

#endif