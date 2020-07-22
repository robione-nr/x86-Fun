<p><b>You chose the blue pill!</b> I wanted to begin to finally organize and archive my code. Some of my source files are getting a bit cluttered with various versions commented out, etc. I didn't want to throw them away. I figure I (or someone online) might find them useful at a later date or if I come across some older hardware.</p>

<p>Right now I started to tinker with some image processing and computer vision algorithms and that's where I'll start my posts. I intend on creating the ability for people to leave comments. I'm eager to hear them, whether it's because the code was useful or a way to improve it (i.e. using good practices or tricks... I'm self-taught so some of these aren't obvious to me).</p>

<p><b>Note:</b> Any code I've benchmarked is where speed is somewhat important to me and is given in iterations per minute. Because of multithreading, single/multiple processors, etc. consider the number given to be approximate. Right now things are benched on my netbook which is the following environment:
<ul>
	<li><b>OS:</b> Windows XP Home Edition SP3 32-bit</li>
	<li><b>CPU:</b> Intel Atom N270 1.6GHz Single core</li>
	<li><b>GFX:</b> Intel 945 Express Chipset</li>
	<li><b>Compiler:</b> VC++ 98 SP5 w/ Processor Pack</li>
	<li><b>Compiler options:</b> <span class="note">/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"Release/edge.pch" /Yu"stdafx.h" /Fo"Release/" /Fd"Release/" /FD /c</span></li>
</ul>
</p>