<table>
	<tr>
		<td><b>Purpose:</b></td>
		<td>Implement the Laplace edge detection algorithm efficiently with speeds suitable for real-time applications on full screen capture data.<br/>&nbsp;</td>
	</tr>
	<tr>
		<td><b>Overview:</b></td>
		<td>Where as Sobel approximates the first derivative in regards to the change in signal strength that occurs at an edge boundary, Laplace approximates the second derivative. As such it is much more sensitive to noise. Another difference is that the algorithm uses one 5x5 convolution mask which is moved over the image and calculates the center pixel at each iteration. The mask is not sensitive to rotations like Sobel and is why only one is needed. The values used are:<br/><br/>
		<pre>			[-1,-1,-1,-1,-1]
			[-1,-1,-1,-1,-1]
		M = 	[-1,-1,24,-1,-1]
			[-1,-1,-1,-1,-1]
			[-1,-1,-1,-1,-1]
		</pre>
		</td>
	</tr>
	<tr>
		<td><b>Restrictions:</b></td>
		<td class="sm"><ul><li>None at present.</li></ul>
		</td>
	</tr>
		<tr>
		<td><b>Notes:</b></td>
		<td>I had done some work on the original code which I found from a Google search which led me <a href="http://www.pages.drexel.edu/~weg22/edge.html" target="_nrother">here</a>. The code on that page is the epitome of unoptimized, but in doing so it is relatively easy to see how the algorithm is implemented. It is included below for comparative purposes. I wrote a C++ version based off his code.</br>&nbsp;
		</td>
	</tr>
	<tr>
		<td><b>Versions:</b></td>
		<td>
			<table class="src_version" style="width:80%" border="1px">
				<tr><th></th><th>Iterations per Minute<sup class="ex_sm">1</sup></th></tr>
				<tr><td><a href="src|source/laplace_ref.cpp" onclick="ajaxRequest(this,'url_href'); return false;">Laplace - Reference</a><sup class="ex_sm">2</sup></td><td>~464</td></tr>
				<tr><td><a href="src|source/laplace_gy.cpp" onclick="ajaxRequest(this,'url_href'); return false;">C++ - Original</a><sup class="ex_sm">2</sup></td><td>~2,860</td></tr>
			</table>
			<div class="ex_sm" style="padding-left:47px"><br/>
				<sup>1</sup> Screen resolution 1024 x 576 x 32<br/>
				<sup>2</sup> No restrictions on source buffer size<br/>
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