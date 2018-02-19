package org.negasoft;

public class ByteProcess {
	   static {
		      System.loadLibrary("processor"); // Load native library at runtime
		   }
	   public native byte[] process(byte[] value);
}
