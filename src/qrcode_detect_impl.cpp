#include <iostream>
#include <fstream>
#include <string>
#include "ImageReaderSource.h"
#include <zxing/common/Counted.h>
#include <zxing/Binarizer.h>
#include <zxing/MultiFormatReader.h>
#include <zxing/Result.h>
#include <zxing/ReaderException.h>
#include <zxing/common/GlobalHistogramBinarizer.h>
#include <zxing/common/HybridBinarizer.h>
#include <exception>
#include <zxing/Exception.h>
#include <zxing/common/IllegalArgumentException.h>
#include <zxing/BinaryBitmap.h>
#include <zxing/DecodeHints.h>

#include <zxing/qrcode/QRCodeReader.h>
#include <zxing/multi/qrcode/QRCodeMultiReader.h>
#include <zxing/multi/ByQuadrantReader.h>
#include <zxing/multi/MultipleBarcodeReader.h>
#include <zxing/multi/GenericMultipleBarcodeReader.h>

using namespace std;
using namespace zxing;
using namespace zxing::multi;
using namespace zxing::qrcode;

bool try_harder = false;
bool search_multi = false;
bool use_hybrid = true;

static int read_image(Ref<LuminanceSource> source, bool hybrid, bool pure_barcode, vector<Ref<Result> > &results);

extern "C" const char *single_detect_file(const char *filename, bool pure_barcode, int *hresult)
{
	*hresult = 1;
	Ref<LuminanceSource> source;
	try {
		source = ImageReaderSource::create(filename);
	} catch (const zxing::IllegalArgumentException &e) {
		*hresult = -1;
		return NULL;
	}
	vector<Ref<Result> > results;
	*hresult = read_image(source, use_hybrid, pure_barcode, results);
	if (*hresult != 0) {
		return NULL;
	}
	return results[0]->getText()->getText().c_str();
}

extern "C" const char *single_detect_memory(const char* ptr, size_t size, int image_type, bool pure_barcode, int *hresult)
{
	*hresult = 1;
	Ref<LuminanceSource> source;
	try {
		source = ImageReaderSource::create((const unsigned char *)ptr, size, image_type);
	} catch (const zxing::IllegalArgumentException &e) {
		*hresult = -1;
		return NULL;
	}
	vector<Ref<Result> > results;
	*hresult = read_image(source, use_hybrid, pure_barcode, results);
	if (*hresult != 0) {
		return NULL;
	}
	return results[0]->getText()->getText().c_str();
}

vector<Ref<Result> > decode_multi(Ref<BinaryBitmap> image, DecodeHints hints) {
  MultiFormatReader delegate;
  GenericMultipleBarcodeReader reader(delegate);
  return reader.decodeMultiple(image, hints);
}

vector<Ref<Result> > decode(Ref<BinaryBitmap> image, DecodeHints hints) {
  Ref<Reader> reader(new MultiFormatReader);
  return vector<Ref<Result> >(1, reader->decode(image, hints));
}

static int read_image(Ref<LuminanceSource> source, bool hybrid, bool pure, vector<Ref<Result> > &results) {
	string cell_result;
	int res = -1;

	try {
		Ref<Binarizer> binarizer;
		if (hybrid) {
			binarizer = new HybridBinarizer(source);
		} else {
			binarizer = new GlobalHistogramBinarizer(source);
		}
		DecodeHints hints(DecodeHints::DEFAULT_HINT);
		if (pure)
			hints.addFormat(BarcodeFormat::PURE_BARCODE);
		hints.setTryHarder(try_harder);
		Ref<BinaryBitmap> binary(new BinaryBitmap(binarizer));
		if (search_multi) {
			results = decode_multi(binary, hints);
		} else {
			results = decode(binary, hints);
		}
		res = 0;
	} catch (const ReaderException& e) {
		cell_result = "zxing::ReaderException: " + string(e.what());
		res = -2;
	} catch (const zxing::IllegalArgumentException& e) {
		cell_result = "zxing::IllegalArgumentException: " + string(e.what());
		res = -3;
	} catch (const zxing::Exception& e) {
		cell_result = "zxing::Exception: " + string(e.what());
		res = -4;
	} catch (const std::exception& e) {
		cell_result = "std::exception: " + string(e.what());
		res = -5;
	}
	if (res) {
		cerr << cell_result << endl;
	}
	return res;
}

