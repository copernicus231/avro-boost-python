package org.negasoft;

import java.io.ByteArrayOutputStream;
import java.io.IOException;

import org.apache.avro.Schema;
import org.apache.avro.generic.GenericDatumWriter;
import org.apache.avro.generic.GenericRecord;
import org.apache.avro.io.BinaryEncoder;
import org.apache.avro.io.DatumWriter;
import org.apache.avro.io.EncoderFactory;

public class PythonAvroProcessor {

	ByteProcess bp = new ByteProcess();
	BinaryEncoder encoder;
	ByteArrayOutputStream stream = new ByteArrayOutputStream();
	DatumWriter<GenericRecord> datumWriter;
	
	public PythonAvroProcessor(Schema schema) {
		datumWriter=new GenericDatumWriter<GenericRecord>(schema);
	}
	public void process(GenericRecord user) throws IOException {
		encoder = EncoderFactory.get().binaryEncoder(stream, encoder);
		datumWriter.write(user, encoder);
		encoder.flush();
		byte[] r = bp.process(stream.toByteArray());
		stream.reset();
		System.out.println("length:"+r.length);
	}
}
