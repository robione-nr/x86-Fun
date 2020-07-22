<table>
	<tr>
		<td><b>Purpose:</b></td>
		<td>Implement the Sobel edge detection algorithm efficiently with speeds suitable for real-time applications on full screen capture data.<br/>&nbsp;</td>
	</tr>
	<tr>
		<td><b>Overview:</b></td>
		<td>Sobel edge detection attempts to approximate the change in signal strength that one normally encounters at an edge boundary. The input signal can be luminosity (for a greyscale image), individual color channels, etc. The algorithm is implemented by moving two 3x3 convolution masks over the image and calculating the center pixel at each iteration. One mask finds horizontal edges, the other, vertical. They are:<br/><br/>
		<pre>		[-1, 0, 1]			[ 1, 2, 1]
	X = 	[-2, 0, 2]		Y = 	[ 0, 0, 0]
		[-1, 0, 1]			[-1,-2,-1]
		</pre>
		</td>
	</tr>
	<tr>
		<td><b>Restrictions:</b></td>
		<td class="sm"><ul><li>Source buffer size must account for out-of-bounds read at end of loop in SSE color version.</li>
			<li>Source image width must be divisible by 8 in greyscale SSE version.</li>
			<li>Source image data is 32 bits or 8 bits per pixel, depending on color or greyscale implementation.</li>
			<!liGreyscale SSE implementation assumes source data is aligned properly on byte boundaries during greyscale conversion.</li></ul>
		</td>
	</tr>
		<tr>
		<td><b>Notes:</b></td>
		<td>I also received some advise from masm32.com forum members here as well. I had done some work on the original code which I found from a Google search which led me <a href="http://www.pages.drexel.edu/~weg22/edge.html" target="_nrother">here</a>. The code on that page is the epitome of unoptimized, but in doing so it is relatively easy to see how the algorithm is implemented. It is included below for comparative purposes. I wrote a C++ and x86 assembly version based off his code before I had hit the forums. Once again their help was indispensable in nudging me in the proper direction.<br/><br/>Most of what I've done involved working with greyscale images. But I felt that edges may not properly be found in those images because the color data has been stripped away. Hence there exists, in theory, possible adjacent colors that will produce undetectable or weakened edges. This does occur but the occurrence is rather low. In any case, I have coded a color Sobel algorithm as well.</br>&nbsp;
		</td>
	</tr>
	<tr>
		<td><b>Versions:</b></td>
		<td>
			<table class="src_version" style="width:80%" border="1px">
				<tr><th></th><th>Iterations per Minute<sup class="ex_sm">1</sup></th></tr>
				<tr><td><a href="src|source/sobel_ref.cpp" onclick="ajaxRequest(this,'url_href'); return false;">Sobel - Reference</a><sup class="ex_sm">2</sup></td><td>~625</td></tr>
				<tr><td><a href="src|source/sobel_gy.cpp" onclick="ajaxRequest(this,'url_href'); return false;">C++ - Original</a><sup class="ex_sm">2</sup></td><td>~3,880</td></tr>
				<tr><td><a href="src|source/sobel_gy.x86" onclick="ajaxRequest(this,'url_href'); return false;">Assembly - x86</a><sup class="ex_sm">23</sup></td><td>~3,860</td></tr>
				<tr><td><a href="src|source/sobel_gy2.cpp" onclick="ajaxRequest(this,'url_href'); return false;">C++ - Reduced Reads</a><sup class="ex_sm">2</sup></td><td>~4,350</td></tr>
				<tr><td><a href="src|source/sobel_clr.sse" onclick="ajaxRequest(this,'url_href'); return false;">Assembly (Color) - SSE2</a></td><td>~3,900</td></tr>
				<tr><td><a href="src|source/sobel_gy.sse" onclick="ajaxRequest(this,'url_href'); return false;">Assembly - SSE2</a></td><td>~28,500</td></tr>
			</table>
			<div class="ex_sm" style="padding-left:47px"><br/>
				<sup>1</sup> Screen resolution 1024 x 576 x 32<br/>
				<sup>2</sup> No restrictions on source buffer size<br/>
				<sup>3</sup> Faster results were obtained when using simpler addressing in MOVZX instructions.<br/>
				<p>Please note that Windows stores pixel data in BGRA format. If using OpenGL like I am, OpenGL expects data in RGBA format.</p>
			</div>
			<br/>&nbsp;
		</td>
	</tr>
	<tr>
		<td colspan="2"><b>Code:</b><code id="src">Click link in version table</code></td>	
	</tr>
</table>
<br/>