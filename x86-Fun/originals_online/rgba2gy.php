<table>
	<tr>
		<td><b>Purpose:</b></td>
		<td>Implement a RGBA to greyscale converter to reduce per pixel computations in later algorithms. Data will change from 32-bits per pixel to 8-bits per pixel in the process.<br/>&nbsp;</td>
	</tr>
		<td><b>Restrictions:</b></td>
		<td class="sm"><ul><li>Source image width must be divisible by 4.</li>
			<li>Source image data is 32 bits per pixel.</li>
			<li>Destination buffer is 8 bits per pixel.</li></ul>
		</td>
	</tr>
		<tr>
		<td><b>Notes:</b></td>
		<td>A decent amount of time was spent learning tips and tricks on this simple function as the lessons would carryover into other, more complex, methods. This began simply as a very short floating point implementation in C. Because this is intended to be used for real-time applications much improvement was needed and it was converted over to SSE. At this point I sought the advice from the people at the masm32.com forums. They were very helpful and the code had been modified to use an integer math approximation with near identical results. I then unrolled and streamlined the loop and added cache instructions to improve performance.</br>&nbsp;
		</td>
	</tr>
	<tr>
		<td><b>Versions:</b></td>
		<td>
			<table class="src_version" style="width:80%" border="1px">
				<tr><th></th><th>Iterations per Minute<sup class="ex_sm">1</sup></th></tr>
				<tr><td><a href="src|source/rgba2gy_f.cpp" onclick="ajaxRequest(this,'url_href'); return false;">C++ - FP Math</a><sup class="ex_sm">2</sup></td><td>~1,820</td></tr>
				<tr><td><a href="src|source/rgba2gy_f.sse" onclick="ajaxRequest(this,'url_href'); return false;">Assembly (FP) - SSE2</a></td><td>~13,300</td></tr>
				<tr><td><a href="src|source/rgba2gy.mmx" onclick="ajaxRequest(this,'url_href'); return false;">Assembly - MMX</a></td><td>~14,100</td></tr>
				<tr><td><a href="src|source/rgba2gy_i.sse" onclick="ajaxRequest(this,'url_href'); return false;">Assembly (Int) - SSE2</a></td><td>~23,900</td></tr>
				<tr><td><a href="src|source/rgba2gy_i2.sse" onclick="ajaxRequest(this,'url_href'); return false;">Assembly (Int/Unrolled) - SSE2</a><sup class="ex_sm">3</sup></td><td>~27,400</td></tr>
				<tr><td><a href="src|source/rgba2gy_i3.sse" onclick="ajaxRequest(this,'url_href'); return false;">Assembly (Cache) - SSE2</a><sup class="ex_sm">3</sup></td><td>~30,400</td></tr>
				<tr><td><a href="src|source/rgba2gy_i.cpp" onclick="ajaxRequest(this,'url_href'); return false;">C++ - Integer Math</a><sup class="ex_sm">2</sup></td><td>~4,930</td></tr>
			</table>
			<div class="ex_sm" style="padding-left:47px"><br/>
				<sup>1</sup> Screen resolution 1024 x 576 x 32<br/>
				<sup>2</sup> No restrictions on source buffer size<br/>
				<sup>3</sup> Source image width must be divisible by 8<br/>
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