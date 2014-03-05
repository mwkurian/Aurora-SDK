////////////////////////////////////////////////////////////////////////////////
// Filename: horizontalblur.fx
////////////////////////////////////////////////////////////////////////////////


/////////////
// GLOBALS //
/////////////
matrix worldMatrix;
matrix viewMatrix;
matrix projectionMatrix;
Texture2D shaderTexture;
float screenWidth = 569;


///////////////////
// SAMPLE STATES //
///////////////////
SamplerState SampleType
{
	Filter = ANISOTROPIC;
	AddressU = Clamp;
	AddressV = Clamp;
};

// MK Gaussian kernel creator - Javascript
//
//function getGaussianKernel(xRadius)
//{
//	if (xRadius < 1)
//	{
//		return NULL;
//	}
//
//	var dataLength = xRadius * 2 + 1;
//
//	var data = new Array();
//
//	var sigma = xRadius / 3.0;
//	var twoSigmaSquare = 2.0 * sigma * sigma;
//	var sigmaRoot = parseFloat(Math.sqrt(twoSigmaSquare * 3.14159));
//	var total = 0.0;
//
//	for (var i = -xRadius; i <= xRadius; i++)
//	{
//		var distance = parseFloat(i * i);
//		var index = i + xRadius;
//		data[index] = parseFloat(Math.exp(-distance / twoSigmaSquare) / sigmaRoot);
//		total += data[index];
//	}
//
//	for (var i = 0; i < dataLength; i++)
//	{
//		data[i] /= total;
//	}
//
//	return data;
//}
//
//function getPixelKernel(radius)
//{
//	var data = new Array();
//	for (var i = -radius; i < radius + 1; i++)
//		data.push(i);
//	return data;
//}
//
//function getGaussian(radius) {
//	var pKernel = getPixelKernel(radius);
//	var data = "static const float kernel[" + (radius * 2 + 1) + "] = { " + pKernel + " };";
//	var gKernel = getGaussianKernel(radius);
//
//	console.log((data += "\nstatic const float weights[" + (radius * 2 + 1) + "] = { " + gKernel + " };"));
//}


static const float kernel[71] = { -35, -34, -33, -32, -31, -30, -29, -28, -27, -26, -25, -24, -23, -22, -21, -20, -19, -18, -17, -16, -15, -14, -13, -12, -11, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35 };
static const float weights[71] = { 0.0003807622546203966, 0.0004906075713239298, 0.0006275146475665876, 0.0007967512511978494, 0.0010042247151735896, 0.0012564590020428406, 0.0015605403549293344, 0.0019240260617353522, 0.0023548115760058564, 0.0028609524435996955, 0.0034504392107541446, 0.004130925733511176, 0.004909414025601617, 0.005791901878532406, 0.006783002820292805, 0.007885551356100562, 0.009100209623188193, 0.010425094330359048, 0.011855444869280772, 0.013383354515985572, 0.014997586460270714, 0.01668349483977855, 0.018423067929526624, 0.02019510616337774, 0.021975541872002763, 0.023737900759758415, 0.025453897567563877, 0.027094150528650975, 0.028628991630285667, 0.030029342884658923, 0.03126762330730229, 0.03231864756219319, 0.03316047561713765, 0.03377517348083519, 0.034149448220632206, 0.03427512586844698, 0.034149448220632206, 0.03377517348083519, 0.03316047561713765, 0.03231864756219319, 0.03126762330730229, 0.030029342884658923, 0.028628991630285667, 0.027094150528650975, 0.025453897567563877, 0.023737900759758415, 0.021975541872002763, 0.02019510616337774, 0.018423067929526624, 0.01668349483977855, 0.014997586460270714, 0.013383354515985572, 0.011855444869280772, 0.010425094330359048, 0.009100209623188193, 0.007885551356100562, 0.006783002820292805, 0.005791901878532406, 0.004909414025601617, 0.004130925733511176, 0.0034504392107541446, 0.0028609524435996955, 0.0023548115760058564, 0.0019240260617353522, 0.0015605403549293344, 0.0012564590020428406, 0.0010042247151735896, 0.0007967512511978494, 0.0006275146475665876, 0.0004906075713239298, 0.0003807622546203966 }; 

//////////////
// TYPEDEFS //
//////////////
struct VertexInputType
{
    float4 position : POSITION;
    float2 tex : TEXCOORD0;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
};


////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
PixelInputType HorizontalBlurVertexShader(VertexInputType input)
{
    PixelInputType output;

	// Force w-buffer to be 1.0
	output.position.w = 1.0f;

	// Calculate z-buffer manually
	output.position.z = (10000000 - input.position.z) / 10000000;

	// Calculate the position of the vertex 
	// against the world, view, and projection matrices.
	output.position = input.position;

	// Store the texture coordinates for the pixel shader.
    output.tex = input.tex;
	
	return output;
}


////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 HorizontalBlurPixelShader(PixelInputType input) : SV_Target
{
	// Determine the floating point size of a texel for a screen with this specific width.
	float texelSize = 1.0f / screenWidth;
	float4 color = float4(0.0f, 0.0f, 0.0f, 0.0f);

	for (int i = 0; i < 71; i++)
	{
		color += shaderTexture.Sample(SampleType, input.tex + float2(texelSize * kernel[i], 0.0f)) * weights[i];
	}

	color.a = 1;

	return color;
}


////////////////////////////////////////////////////////////////////////////////
// Technique
////////////////////////////////////////////////////////////////////////////////
technique10 MainTechnique
{
    pass pass0
    {
        SetVertexShader(CompileShader(vs_4_0, HorizontalBlurVertexShader()));
        SetPixelShader(CompileShader(ps_4_0, HorizontalBlurPixelShader()));
        SetGeometryShader(NULL);
    }
}