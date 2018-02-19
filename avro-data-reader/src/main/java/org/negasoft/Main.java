package org.negasoft;

import java.io.File;
import java.io.IOException;

import org.apache.avro.Schema;
import org.apache.avro.file.DataFileReader;
import org.apache.avro.generic.GenericDatumReader;
import org.apache.avro.generic.GenericRecord;
import org.apache.avro.io.DatumReader;

public class Main {

	public static void main(String[] args) {
		
		try {
			Schema schema;
			File file;
			schema = new Schema.Parser().parse(new File("src/main/resources/record.json"));
			file = new File("src/main/resources/record.avro");
			PythonAvroProcessor processor = new PythonAvroProcessor(schema);
		
		DatumReader<GenericRecord> datumReader = new GenericDatumReader<GenericRecord>(schema);
		DataFileReader<GenericRecord> dataFileReader = new DataFileReader<GenericRecord>(file, datumReader);
		GenericRecord user = null;
		while (dataFileReader.hasNext()) {
		// Reuse user object by passing it to next(). This saves us from
		// allocating and garbage collecting many objects for files with
		// many items.
			user = dataFileReader.next(user);
			long startTime = System.currentTimeMillis();
			processor.process(user);
			long endTime = System.currentTimeMillis();
			System.out.println("time:"+ (endTime-startTime));
		
		}
		dataFileReader.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
