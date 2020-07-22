<table>
	<tr>
		<td><b>Purpose:</b></td>
		<td>Update an old 3D vector class I wrote back in 2001 to use SIMD instructions. This will then be implemented in <i>n</i>-dimensional vectors to be used in neural nets... and will ideally show an increase in performance for most network topologies. Both are specialized classes intended for specific uses but given enough functionality so they wouldn't necessarily be limited to them. Because I need the ANN to be fast I'll probably write more classes (i.e. 4/8/12 - D vectors) but won't post them. It's just loop unrolling anyway.<br/>&nbsp;</td>
	</tr>
		<td><b>Restrictions:</b></td>
		<td class="sm"><ul><li>Interface does not allow for operator chaining.</li</ul>
		</td>
	</tr>
		<tr>
		<td><b>Notes:</b></td>
		<td>There is nothing exceedingly special about these classes. Placing them online is more for archival purposes than anything else. More performance may be squeaked out but due to my dated compiler I don't have intrinsics for SSE2 instructions. I decided to use instrinsics wherever I could as I'm not sure how the compiler handles switching to/from inline x86/SSE as opposed to remaining in C/C++ within the same function. Something I can look into in the future. Everything in the 3-D vector is inlined and the class names are not quite conventional.... as this has the same interface as my old vector class I just wanted to drop it in without any further editting. The old name was a typedef:<br/><br/><pre>typedef C_Vector3D&lt;float&gt; fVector3D;</pre><br/><br/>
		I switched to inline assembly for the <i>n</i>-dimensional vectors. My compiler didn't produce optimal results in release builds when I unrolled the loop 2x:
		<pre>
	__m128 c = _mm_load1_ps(&scalar);
	int i = 0;

	if(m_iElements & 0x01) {
		*(m_pdata) = _mm_mul_ps(*(m_pdata),c);
		++i;
	}
	for(;i&lt;m_iElements;i+=2) {
		*(m_pdata+i) = _mm_mul_ps(*(m_pdata+i),c);
		*(m_pdata+i+1) = _mm_mul_ps(*(m_pdata+i+1),c);
	}
</pre>A simple optimization became <a href="src|source/vector_op_x_self_compiler.x86" onclick="ajaxRequest(this,'url_href'); return false;">this</a>. <span class="sm">(Refer to code section below.)</span> My code, because of the push/pops the compiler inserted has only 3 fewer instructions but has an ~50% performance increase as I reordered instructions for better pipelining. Compare the area below line 49 (compiler output) to any arithmatic operation for the <i>n</i>-dimensional vector below the label _even.<br/>&nbsp;
		</td>
	</tr>
	<tr>
		<td><b>Versions:</b></td>
		<td>
			<table class="src_version" style="width:80%" border="1px">
				<tr><th></th><th>Performance Gain<sup class="ex_sm">1</sup></th></tr>
				<tr><td><a href="src|source/vector3d.cpp" onclick="ajaxRequest(this,'url_href'); return false;">3D inline and <i>n</i>-D class</a></td><td>~50% average</td></tr>
				<tr><td><a href="src|source/vectornd.cpp" onclick="ajaxRequest(this,'url_href'); return false;"><i>n</i>-D Vector Source</a></td><td>UNK (no base comparison)</td></tr>
			</table>
			<div class="ex_sm" style="padding-left:47px"><br/>
				<sup>1</sup> Dependent on which method is called vs. my previous vector class. Also gains may be more. I found it difficult to time some code in release builds due to optimizations.
			</div>
			<br/>&nbsp;
		</td>
	</tr>
	<tr>
		<td colspan="2"><b>Code:</b><code id="src">Click link in version table</code></td>	
	</tr>
</table>
<br/>