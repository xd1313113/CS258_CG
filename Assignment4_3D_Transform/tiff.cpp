#include "tiff.h"
#include <string.h>
#include <algorithm>
#include <fstream>
#include <string>
#include <iostream>


Tiff *img;
extern Context *ctx;
extern GLubyte checkImage[1024][1024][3];
extern void makeCheckImage(void);
extern int width_W, height_W;

using namespace std;

/** @brief (one liner)
  *
  * (documentation goes here)
  */
void TiffHelper::reverser_str(char *str)
{
    int i = 0, j = strlen(str) - 1;
    cout<<strlen(str)<<std::endl;
    while (i < j)
    {
        char tmp = str[i];
        str[i++] = str[j];
        str[j--] = tmp;
    }
}

/** @brief (one liner)
  *
  * (documentation goes here)
  */
template <class T>
void TiffHelper::endianswap(T *objp)
{
    unsigned char *memp = reinterpret_cast<unsigned char*>(objp);
    reverse(memp, memp + sizeof(T));
}
/** @brief (one liner)
  *
  * (documentation goes here)
  */
int TiffHelper::IsLittleEndian()
{
    short int one = 1;
    char *byte = (char *) &one;
    return(byte[0] ? TIFF_LITTLE_ENDIAN : TIFF_BIG_ENDIAN);
}

void TiffHelper::reset(Tiff *ptr)
{
    delete ptr;
    ptr=0;
}


string TiffHelper::getTagName(int tag)
{
    switch(tag)
    {

    case NewSubfileType:
        return "NewSubfileType";
    case SubfileType:
        return "SubfileType";
    case ImageWidth:
        return "ImageWidth";
    case ImageLength:
        return "ImageLength";
    case BitsPerSample:
        return "BitsPerSample";
    case Compression:
        return "Compression";
    case PhotometricInterpretation:
        return "PhotometricInterpretation";
    case Threshholding:
        return "Threshholding";
    case CellWidth:
        return "CellWidth";
    case CellLength:
        return "CellLength";
    case FillOrder:
        return "FillOrder";
    case DocumentName:
        return "DocumentName";
    case ImageDescription:
        return "ImageDescription";
    case Make :
        return "Make";
    case Model:
        return "Model";
    case StripOffsets:
        return "StripOffsets";
    case Orientation:
        return "Orientation";
    case SamplesPerPixel:
        return "SamplesPerPixel";
    case RowsPerStrip:
        return "RowsPerStrip";
    case StripByteCounts:
        return "StripByteCounts";
    case MinSampleValue:
        return "MinSampleValue";
    case MaxSampleValue:
        return "MaxSampleValue";
    case XResolution:
        return "XResolution";
    case YResolution:
        return "YResolution";
    case PlanarConfiguration:
        return "PlanarConfiguration";
    case PageName:
        return "PageName";
    case XPosition:
        return "XPosition";
    case YPosition:
        return "YPosition";
    case FreeOffsets:
        return "FreeOffsets";
    case FreeByteCounts:
        return "FreeByteCounts";
    case GrayResponseUnit:
        return "GrayResponseUnit";
    case GrayResponseCurve:
        return "GrayResponseCurve";
    case T4Options:
        return "T4Options";
    case T6Options:
        return "T6Options";
    case ResolutionUnit:
        return "ResolutionUnit";
    case PageNumber:
        return "PageNumber";
    case TransferFunction :
        return "TransferFunction";
    case Software:
        return "Software";
    case DateTime:
        return "DateTime";
    case Artist:
        return "Artist";
    case HostComputer:
        return "HostComputer";
    case Predictor:
        return "Predictor";
    case WhitePoint:
        return "WhitePoint";
    case PrimaryChromaticities:
        return "PrimaryChromaticities";
    case ColorMap:
        return "ColorMap";
    case HalftoneHints:
        return "HalftoneHints";
    case TileWidth:
        return "TileWidth";
    case TileLength:
        return "TileLength";
    case TileOffsets:
        return "TileOffsets";
    case TileByteCounts:
        return "TileByteCounts";
    case InkSet:
        return "InkSet";
    case InkNames:
        return "InkNames";
    case NumberOfInks:
        return "NumberOfInks";
    case DotRange:
        return "DotRange";
    case TargetPrinter:
        return "TargetPrinter";
    case ExtraSamples:
        return "ExtraSamples";
    case SampleFormat:
        return "SampleFormat";
    case SMinSampleValue:
        return "SMinSampleValue";
    case SMaxSampleValue:
        return "SMaxSampleValue";
    case TransferRange:
        return "TransferRange";
    case JPEGProc:
        return "JPEGProc";
    case JPEGInterchangeFormat:
        return "JPEGInterchangeFormat";
    case JPEGInterchangeFormatLngth:
        return "JPEGInterchangeFormatLngth";
    case JPEGRestartInterval:
        return "JPEGRestartInterval";
    case PEGLosslessPredictors:
        return "PEGLosslessPredictors";
    case JPEGPointTransforms:
        return "JPEGPointTransforms";
    case JPEGQTables:
        return "JPEGQTables";
    case JPEGDCTables:
        return "JPEGDCTables";
    case JPEGACTables:
        return "JPEGACTables";
    case YCbCrCoefficients:
        return "YCbCrCoefficients";
    case YCbCrSubSampling :
        return "YCbCrSubSampling";
    case YCbCrPositioning:
        return "YCbCrPositioning";
    case ReferenceBlackWhite :
        return "ReferenceBlackWhite";
    case Copyright:
        return "Copyright";
    }
    return "";

}
string TiffHelper::getTypeName(int type)
{

    switch(type)
    {
    case TIFF_NOTYPE:
        return "Unknown Type";     /* placeholder */
    case  TIFF_BYTE:
        return "BYTE";         /* 8-bit unsigned integer */
    case TIFF_ASCII:
        return "ASCII";        /* 8-bit bytes w/ last byte null */
    case TIFF_SHORT:
        return "SHORT";         /* 16-bit unsigned integer */
    case TIFF_LONG:
        return "LONG";         /* 32-bit unsigned integer */
    case TIFF_RATIONAL:
        return "RATIONAL";      /* 64-bit unsigned fraction */
    case TIFF_SBYTE:
        return "SBYTE";         /* !8-bit signed integer */
    case TIFF_UNDEFINED:
        return "UNDEFINED";     /* !8-bit untyped data */
    case TIFF_SSHORT:
        return "SSHORT";        /* !16-bit signed integer */
    case TIFF_SLONG:
        return "SLONG";         /* !32-bit signed integer */
    case TIFF_SRATIONAL:
        return "SRATIONAL";   /* !64-bit signed fraction */
    case TIFF_FLOAT:
        return "FLOAT";        /* !32-bit IEEE floating point */
    case TIFF_DOUBLE:
        return "DOUBLE";       /* !64-bit IEEE floating point */
    }
    return "";
}


void TiffHelper::printTAG(short Tag, short fType, int count_value, int value_offset)
{
    cout<<getTagName(Tag)<<" ("<<Tag<<") "<<getTypeName(fType)<<" ("<<fType<<") "<<count_value<<" Values: "<<value_offset<<";"<<endl;
}
/** @brief TiffRead
  *
  * @todo: document this function
  */
TiffRead::TiffRead(string file):filename(file)
{

}

/** @brief ~TiffRead
  *
  * @todo: document this function
  */
TiffRead::~TiffRead()
{

}
/** @brief execute
  *
  * @todo: document this function
  */
void TiffRead::execute()
{
    cout<<"Reading"<<filename<<endl;

    string line;

    ifstream mFile(filename.c_str(),ios::binary);
    if(!mFile)
    {
        cout << "Could not open the given file, please check and try again" << std::endl;
    }
    else
    {
        if(img != 0)
        {
            reset(img);
        }
        img = new Tiff();
        mFile.seekg(0, ios::beg);
        mFile.read((char *)&img->header.tiff_endian, 2);

        if( img->header.tiff_endian == 18761 ) // little endian file
        {
            mConvert = IsLittleEndian()?false:true;
            img->mEndian_Convert = mConvert;
        }
        else if( img->header.tiff_endian == 19789 )
        {
            mConvert = IsLittleEndian()?true:false;
            img->mEndian_Convert = mConvert;
        }
        else
        {
            cout<<"Not a tiff file !"<<endl;
            mFile.close();
            reset(img);
            return;
        }

        mFile.read((char *)&img->header.tiff_magic, 2);

        if(img->mEndian_Convert) endianswap(&img->header.tiff_magic);

        if(img->header.tiff_magic != 42)
        {
            cout<<"Not a tiff file !"<<endl;
            mFile.close();
            reset(img);
            return;
        }

        mFile.read((char *)&img->header.tiff_diroff, 4);
        if(img->mEndian_Convert) endianswap(&img->header.tiff_diroff);

        mFile.seekg(img->header.tiff_diroff, ios::beg);
        mFile.read((char *)&img->count_entry, 2);
        if(img->mEndian_Convert) endianswap(&img->count_entry);

//        cout<<img->header.tiff_endian<<endl;
//        cout<<img->header.tiff_magic<<endl;
//        cout<<img->header.tiff_diroff<<endl;
//        cout<<img->count_entry<<endl;

        short Tag;
        short fType;
        int count_value;
        int value_offset;

        while(img->count_entry-- > 0)
        {
            mFile.read((char *)&Tag, 2);
            if(img->mEndian_Convert) endianswap(&Tag);

            mFile.read((char *)&fType, 2);
            if(img->mEndian_Convert) endianswap(&fType);

            mFile.read((char *)&count_value, 4);
            if(img->mEndian_Convert) endianswap(&count_value);

            short first;
            short second;
            if(fType == 3)
            {
                mFile.read((char *)&first, 2);
                if(img->mEndian_Convert) endianswap(&first);
                value_offset = first;
                mFile.read((char *)&second, 2);
                if(img->mEndian_Convert) endianswap(&second);
            }
            else
            {
                mFile.read((char *)&value_offset, 4);
                if(img->mEndian_Convert) endianswap(&value_offset);
            }

//            cout<<Tag<<endl;
//            cout<<fType<<endl;
//            cout<<count_value<<endl;
//            cout<<value_offset<<endl;

            switch(Tag)
            {
            case ImageWidth:
                if(value_offset > 1024)
                {
                    mFile.close();
                    reset(img);
                    return;
                }
                img->mImageWidth = value_offset;
                break;
            case ImageLength:
                if(value_offset > 1024)
                {
                    mFile.close();
                    reset(img);
                    return;
                }
                img->mImageLength = value_offset;
                break;
            case BitsPerSample:
                if(count_value == 3)
                {
                    img->mBitsPerSample = 24;
                }
                else
                {
                    img->mBitsPerSample = value_offset;
                }
                break;
            case Compression:
                img->mCompressed = value_offset;
                break;
            case PhotometricInterpretation:
                img->mPhotoMetric = value_offset;
                break;
            case StripOffsets:
            {
                if(count_value == 1) //short
                {
                    img->mStripOffset.push_back(value_offset);
                }
                else if(fType == 3 && count_value == 2)
                {
                    img->mStripOffset.push_back(first);
                    img->mStripOffset.push_back(second);
                }
                else
                {
                    mFile2.open(filename.c_str(), ios::binary);
                    mFile2.seekg(value_offset, ios::beg);
                    if(fType == 3)
                        for(int i = 0; i < count_value; i++)
                        {
                            short temp;
                            mFile2.read((char *) &temp, 2);
                            if(img->mEndian_Convert) endianswap(&temp);
                            img->mStripOffset.push_back(temp);
                        }
                    else if(fType == 4)
                        for(int i = 0; i < count_value; i++)
                        {
                            int temp;
                            mFile2.read((char *) &temp, 4);
                            if(img->mEndian_Convert) endianswap(&temp);
                            img->mStripOffset.push_back(temp);
                        }
                    mFile2.close();
                }
            }
            break;
            case SamplesPerPixel:
                img->mSamplePerPixel = value_offset;
                break;
            case RowsPerStrip:
                img->mRowsPerStrip = value_offset;
                break;
            case StripByteCounts:
            {
                if(fType == 3 && count_value == 1) //short
                {
                    img->mStripByteCounts.push_back(first);
                }
                else if(fType == 3 && count_value == 2)
                {
                    img->mStripByteCounts.push_back(first);
                    img->mStripByteCounts.push_back(second);
                }
                else if(fType == 4 && count_value == 1) //long
                {
                    img->mStripByteCounts.push_back(value_offset);
                }
                else
                {
                    mFile2.open(filename.c_str(), ios::binary);
                    mFile2.seekg(value_offset, ios::beg);
                    if(fType == 3)
                        for(int i = 0; i < count_value; i++)
                        {
                            short temp;
                            mFile2.read((char *) &temp, 2);
                            if(img->mEndian_Convert) endianswap(&temp);
                            img->mStripByteCounts.push_back(temp);
                        }
                    else if(fType == 4)
                        for(int i = 0; i < count_value; i++)
                        {
                            int temp;
                            mFile2.read((char *) &temp, 4);
                            if(img->mEndian_Convert) endianswap(&temp);
                            img->mStripByteCounts.push_back(temp);
                        }
                    mFile2.close();
                }
            }
            break;
            case XResolution:
            {
                unsigned long long int temp;
                mFile2.open(filename.c_str(), ios::binary);
                mFile2.seekg(value_offset, ios::beg);
                mFile2.read((char *)&temp, 8);
                img->mXResolution = temp;
                mFile2.close();
            }
            break;
            case YResolution:
            {
                unsigned long long int temp;
                mFile2.open(filename.c_str(), ios::binary);
                mFile2.seekg(value_offset, ios::beg);
                mFile2.read((char *)&temp, 8);
                img->mYResolution = temp;
                mFile2.close();
            }
            break;
            case ResolutionUnit:
                img->mResolutionUnit = value_offset;
                break;
            }
        }
        try
        {
            makeCheckImage();


            if(img->mBitsPerSample == 8  && img->mCompressed == 1
                    && ( img->mPhotoMetric == 0 || img->mPhotoMetric == 1)) //Grayscale Image
            {
                unsigned char grayScale;
                int row = 0;
                if(img->mRowsPerStrip == 0) throw exception();
                int rowsOfFull = img->mImageLength / img->mRowsPerStrip;
                int rowsOfLastStrip = img->mImageLength % img->mRowsPerStrip;
                //cout<<rowsOfFull<<","<<rowsOfLastStrip<<endl;
                int i;
                for(i = 0; i < rowsOfFull; i++)
                {
                    mFile.seekg(img->mStripOffset.at(i), ios::beg);
                    //cout<<img->mStripOffset.at(i)<<endl;
                    for(int j = 0; j < img->mRowsPerStrip; j++)
                    {
                        for(int k = 0; k < img->mImageWidth; k++)
                        {
                            //cout << i<<", "<<j<<","<<k<<endl;
                            mFile.read((char*)&grayScale, 1);

                            img->mImageData[row][k][0] = (GLubyte)grayScale;
                            img->mImageData[row][k][1] = (GLubyte)grayScale;
                            img->mImageData[row][k][2] = (GLubyte)grayScale;
                            if(img->mPhotoMetric == 0) grayScale = 255 - grayScale;
                            checkImage[img->mImageLength - row -1][k][0] = (GLubyte)grayScale;
                            checkImage[img->mImageLength - row -1][k][1] = (GLubyte)grayScale;
                            checkImage[img->mImageLength - row -1][k][2] = (GLubyte)grayScale;
                            //cout<<row<<","<<k<<","<<(unsigned int)grayScale<<endl;
                        }
                        row++;
                    }


                }
                if(rowsOfLastStrip != 0)
                {
                    //cout<<img->mStripOffset.at(i)<<endl;
                    mFile.seekg(img->mStripOffset.at(i), ios::beg);
                    for(int j = 0; j < rowsOfLastStrip; j++)
                    {
                        for(int k = 0; k < img->mImageWidth; k++)
                        {
                            cout << i<<", "<<j<<","<<k<<endl;
                            mFile.read((char*)&grayScale, 1);

                            img->mImageData[row][k][0] = (GLubyte)grayScale;
                            img->mImageData[row][k][1] = (GLubyte)grayScale;
                            img->mImageData[row][k][2] = (GLubyte)grayScale;
                            if(img->mPhotoMetric == 0) grayScale = 255 - grayScale;
                            checkImage[img->mImageLength - row -1][k][0] = (GLubyte)grayScale;
                            checkImage[img->mImageLength - row -1][k][1] = (GLubyte)grayScale;
                            checkImage[img->mImageLength - row -1][k][2] = (GLubyte)grayScale;
                            cout<<(unsigned int)grayScale<<endl;
                        }
                        row++;
                    }
                }

            }
            else if (img->mBitsPerSample == 24 && img->mCompressed == 1 && img->mPhotoMetric == 2) //RGB image
            {
                unsigned char RGB[3];
                int row = 0;
                if(img->mRowsPerStrip == 0) throw exception();
                int rowsOfFull = img->mImageLength / img->mRowsPerStrip;
                int rowsOfLastStrip = img->mImageLength % img->mRowsPerStrip;
                //cout<<rowsOfFull<<" "<< rowsOfLastStrip<<endl;
                int i;
                for(i = 0; i < rowsOfFull; i++)
                {
                    mFile.seekg(img->mStripOffset.at(i), ios::beg);
                    //cout<<img->mStripOffset.at(i)<<endl;
                    for(int j = 0; j < img->mRowsPerStrip; j++)
                    {
                        for(int k = 0; k < img->mImageWidth; k++)
                        {
                            //cout << i<<", "<<j<<","<<k<<endl;
                            mFile.read((char*)RGB, 3);
                            checkImage[img->mImageLength - row -1][k][0] = img->mImageData[row][k][0] = (GLubyte)RGB[0];
                            checkImage[img->mImageLength - row -1][k][1] = img->mImageData[row][k][1] = (GLubyte)RGB[1];
                            checkImage[img->mImageLength - row -1][k][2] = img->mImageData[row][k][2] = (GLubyte)RGB[2];
                        }
                        row++;

                    }
                }
                if(rowsOfLastStrip != 0)
                {
                    //cout<<img->mStripOffset.at(i)<<endl;
                    mFile.seekg(img->mStripOffset.at(i), ios::beg);
                    for(int j = 0; j < rowsOfLastStrip; j++)
                    {
                        for(int k = 0; k < img->mImageWidth; k++)
                        {
                            //cout << i<<", "<<j<<","<<k<<endl;
                            mFile.read((char*)RGB, 3);
                            checkImage[img->mImageLength - row -1][k][0] = img->mImageData[row][k][0] = (GLubyte)RGB[0];
                            checkImage[img->mImageLength - row -1][k][1] = img->mImageData[row][k][1] = (GLubyte)RGB[1];
                            checkImage[img->mImageLength - row -1][k][2] = img->mImageData[row][k][2] = (GLubyte)RGB[2];
                        }
                        row++;
                    }
                }
            }
            else
            {
                cout<<"Not a 8 bit grayscale uncompressed or a 24 bit RGB uncompressed image!"<<endl;
                mFile.close();
                reset(img);
                return;
            }
            ctx->tiff_hold = true;
        }
        catch(exception &e)
        {
            cout<<"unknow error happen when reading the image data!"<<endl;
        }
    }

    mFile.close();
}

/** @brief TiffStat
  *
  * @todo: document this function
  */
TiffStat::TiffStat() {}

/** @brief TiffStat
  *
  * @todo: document this function
  */
TiffStat::TiffStat(string file):filename(file)
{

}

/** @brief ~TiffStat
  *
  * @todo: document this function
  */
TiffStat::~TiffStat()
{

}

/** @brief execute
  *
  * @todo: document this function
  */
void TiffStat::execute()
{
    cout<<"Stating "<<filename<<endl;
    if(img != 0)
    {
        reset(img);
    }

    img = new Tiff();


    ifstream mFile(filename.c_str(),ios::binary);
    if(!mFile)
    {
        cout << "Could not open the given file, please check and try again" << std::endl;
    }
    else
    {
        mFile.seekg(0, ios::beg);
        mFile.read((char *)&img->header.tiff_endian, 2);

        if( img->header.tiff_endian == 18761 ) // little endian file
        {
            img->mEndian_Convert = IsLittleEndian()?false:true;
            cout<<"Endian: 0x"<<hex<<img->header.tiff_endian<<" Little Endian"<<endl;
        }
        else if( img->header.tiff_endian == 19789 )
        {
            img->mEndian_Convert = IsLittleEndian()?true:false;
            cout<<"Endian: 0x"<<hex<<img->header.tiff_endian<<" Big Endian"<<endl;
        }
        else
        {
            cout<<"Not a tiff file !"<<endl;
            mFile.close();
            reset(img);
            return;
        }

        mFile.read((char *)&img->header.tiff_magic, 2);

        if(img->mEndian_Convert) endianswap(&img->header.tiff_magic);

        if(img->header.tiff_magic != 42)
        {
            cout<<"Not a tiff file !"<<endl;
            mFile.close();
            reset(img);
            return;
        }

        mFile.read((char *)&img->header.tiff_diroff, 4);
        if(img->mEndian_Convert) endianswap(&img->header.tiff_diroff);

        mFile.seekg(img->header.tiff_diroff, ios::beg);
        mFile.read((char *)&img->count_entry, 2);
        if(img->mEndian_Convert) endianswap(&img->count_entry);

        cout<<"Magic: "<<dec<<img->header.tiff_magic<<endl;
        cout<<"IFD Offset: 0x"<<hex<<img->header.tiff_diroff<<endl;
        cout<<"The number of IFD Entry: "<<dec<<img->count_entry<<endl;

        short Tag;
        short fType;
        int count_value;
        int value_offset;

        while(img->count_entry-- > 0)
        {
            mFile.read((char *)&Tag, 2);
            if(img->mEndian_Convert) endianswap(&Tag);

            mFile.read((char *)&fType, 2);
            if(img->mEndian_Convert) endianswap(&fType);

            mFile.read((char *)&count_value, 4);
            if(img->mEndian_Convert) endianswap(&count_value);

            short first;
            short second;
            if(fType == 3 && count_value <= 2)
            {
                mFile.read((char *)&first, 2);
                if(img->mEndian_Convert) endianswap(&first);
                value_offset = first;
                mFile.read((char *)&second, 2);
                if(img->mEndian_Convert) endianswap(&second);
            }
            else
            {
                mFile.read((char *)&value_offset, 4);
                if(img->mEndian_Convert) endianswap(&value_offset);
            }

            //cout<<Tag<<endl;
            //cout<<fType<<endl;
            //cout<<count_value<<endl;
            //cout<<value_offset<<endl;

            switch(Tag)
            {
            case NewSubfileType:
                printTAG(Tag, fType, count_value, value_offset);
                break;
            case ImageWidth:
                printTAG(Tag, fType, count_value, value_offset);
                break;
            case ImageLength:
                printTAG(Tag, fType, count_value, value_offset);
                break;
            case BitsPerSample:
                if(count_value == 1)
                {
                    printTAG(Tag, fType, count_value, value_offset);
                }
                else if(count_value == 3)
                {
                    short temp;
                    mFile2.open(filename.c_str(), ios::binary);
                    mFile2.seekg(value_offset, ios::beg);
                    cout<<getTagName(Tag)<<" ("<<Tag<<") "<<getTypeName(fType)<<" ("<<fType<<") "<<count_value<<" Values:";
                    for ( int i = 0; i < count_value; i++)
                    {
                        mFile2.read((char *)&temp, 2);
                        if(img->mEndian_Convert) endianswap(&temp);
                        cout<<" "<< temp;
                    }
                    cout<<";"<<endl;
                    mFile2.close();
                }
                else
                {
                    cout<<"Do not support format other than 8 bit grayscale and 24 RGB color!"<<endl;
                }
                break;
            case Compression:
                printTAG(Tag, fType, count_value, value_offset);
                break;
            case PhotometricInterpretation:
                printTAG(Tag, fType, count_value, value_offset);
                break;
            case DocumentName:
            {
                int count = count_value;
                string docname ="";
                char temp;
                if(count_value <= 4)
                {
                    while(count-- > 0)
                    {
                        mFile2.read((char*)&temp, 1);
                        docname += temp;
                    }
                }
                else
                {

                    mFile2.open(filename.c_str(), ios::binary);
                    mFile2.seekg(value_offset, ios::beg);

                    while(count-- > 0)
                    {
                        mFile2.read((char*)&temp, 1);
                        docname += temp;
                    }
                    mFile2.close();
                }
                cout<<getTagName(Tag)<<" ("<<Tag<<") "<<getTypeName(fType)<<" ("<<fType<<") "<<count_value<<" Values: "<<docname<<endl;

            }
            break;
            case StripOffsets:
            {
                if(count_value == 1) //short
                {
                    printTAG(Tag, fType, count_value, value_offset);
                }
                else if(fType == 3 && count_value == 2)
                {
                    cout<<getTagName(Tag)<<" ("<<Tag<<") "<<getTypeName(fType)<<" ("<<fType<<") "<<count_value<<" Values: "<<first<<" "<<second<<";"<<endl;
                }
                else
                {
                    mFile2.open(filename.c_str(), ios::binary);
                    mFile2.seekg(value_offset, ios::beg);
                    cout<<getTagName(Tag)<<" ("<<Tag<<") "<<getTypeName(fType)<<" ("<<fType<<") "<<count_value<<" Values:";

                    for(int i = 0; i < count_value; i++)
                    {
                        if(fType == 3)
                        {
                            short temp;
                            mFile2.read((char *) &temp, 2);
                            if(img->mEndian_Convert) endianswap(&temp);
                            cout<<" "<< temp;
                        }
                        else if(fType == 4)
                        {

                            int temp;
                            mFile2.read((char *) &temp, 4);
                            if(img->mEndian_Convert) endianswap(&temp);
                            cout<<" "<< temp;
                        }
                    }
                    cout<<";"<<endl;
                    mFile2.close();
                }
            }
            break;
            case Orientation:
                printTAG(Tag, fType, count_value, value_offset);
                break;
            case SamplesPerPixel:
                printTAG(Tag, fType, count_value, value_offset);
                break;
            case RowsPerStrip:
                printTAG(Tag, fType, count_value, value_offset);
                break;
            case StripByteCounts:
            {
                if(count_value == 1) //short
                {
                    printTAG(Tag, fType, count_value, value_offset);
                }
                else if(fType == 3 && count_value == 2)
                {
                    cout<<getTagName(Tag)<<" ("<<Tag<<") "<<getTypeName(fType)<<" ("<<fType<<") "<<count_value<<" Values: "<<first<<" "<<second<<";"<<endl;
                }
                else
                {
                    mFile2.open(filename.c_str(), ios::binary);
                    mFile2.seekg(value_offset, ios::beg);
                    cout<<getTagName(Tag)<<" ("<<Tag<<") "<<getTypeName(fType)<<" ("<<fType<<") "<<count_value<<" Values:";

                    for(int i = 0; i < count_value; i++)
                    {
                        if(fType == 3)
                        {
                            short temp;
                            mFile2.read((char *) &temp, 2);
                            if(img->mEndian_Convert) endianswap(&temp);
                            cout<<" "<< temp;
                        }
                        else if(fType == 4)
                        {

                            int temp;
                            mFile2.read((char *) &temp, 4);
                            if(img->mEndian_Convert) endianswap(&temp);
                            cout<<" "<< temp;
                        }
                    }
                    cout<<";"<<endl;
                    mFile2.close();
                }
            }
            break;
            case PlanarConfiguration:
                printTAG(Tag, fType, count_value, value_offset);
                break;
            case XResolution:
            {
                int numerator, denominator;
                mFile2.open(filename.c_str(), ios::binary);
                mFile2.seekg(value_offset, ios::beg);
                mFile2.read((char *)&numerator, 4);
                mFile2.read((char *)&denominator, 4);
                if(img->mEndian_Convert) endianswap(&numerator);
                if(img->mEndian_Convert) endianswap(&denominator);
                printTAG(Tag, fType, count_value, numerator/denominator);
                mFile2.close();
            }
            break;
            case YResolution:
            {
                int numerator, denominator;
                mFile2.open(filename.c_str(), ios::binary);
                mFile2.seekg(value_offset, ios::beg);
                mFile2.read((char *)&numerator, 4);
                mFile2.read((char *)&denominator, 4);
                if(img->mEndian_Convert) endianswap(&numerator);
                if(img->mEndian_Convert) endianswap(&denominator);
                printTAG(Tag, fType, count_value, numerator/denominator);
                mFile2.close();
            }
            break;
            case ResolutionUnit:
                printTAG(Tag, fType, count_value, value_offset);
                break;
            default:
                cout<<"unknow or not required Tag"<<endl;
            }

        }
        ctx->tiff_hold = false;
    }
}


/** @brief TiffWrite
  *
  * @todo: document this function
  */
TiffWrite::TiffWrite(string file, int x, int y, int xx, int yy):filename(file),x(x),y(y),xx(xx),yy(yy) {}

/** @brief ~TiffWrite
  *
  * @todo: document this function
  */
TiffWrite::~TiffWrite() {}


/** @brief execute
  *
  * @todo: document this function
  */
void TiffWrite::execute()
{
    cout<<"Writing "<<filename<<endl;

    if(img == 0 )
    {
        //cout<<"Image instance is empty!"<<endl;
        img = new Tiff();
    }

    if(ctx->tiff_hold == false)
    {
        if(IsLittleEndian() == 1)
        {
            img->header.tiff_endian = 18761;
        }
        else
        {
            img->header.tiff_endian = 19789;
        }

        img->header.tiff_magic = 42;

        img->mImageWidth = width_W;
        img->mImageLength = height_W;

        img->mPhotoMetric = 1;
        img->mCompressed = 1;
        unsigned int resolution[2];
        resolution[0] = 72;
        resolution[1] = 1;

        img->mXResolution = (unsigned long long )&resolution;
        img->mYResolution = (unsigned long long )&resolution;
        img->mResolutionUnit = 2;
        img->mEndian_Convert = false;
        img->mBitsPerSample = 8;
        img->mSamplePerPixel = 1;

        for(int j = 0; j < height_W; j++)
        {
            for(int i = 0; i < width_W ; i++)
            {
                img->mImageData[j][i][0] = checkImage[height_W - 1 - j][i][0];
                img->mImageData[j][i][1] = checkImage[height_W - 1 - j][i][1];
                img->mImageData[j][i][2] = checkImage[height_W - 1 - j][i][2];
            }
        }

//        GLubyte * imagedata = new GLubyte[width_W*height_W*3];
//
//        glReadBuffer(GL_BACK_LEFT);
//        glReadPixels((GLint)0,(GLint)0,(GLsizei)width_W, (GLsizei)height_W, GL_RGB, GL_UNSIGNED_BYTE, imagedata);
//
//        cout<<img->mImageData<<endl;
//
//        for(int j = 0; j < height_W; j++)
//        {
//            for(int i = 0; i < width_W ; i++)
//            {
//                img->mImageData[j][i][0] = (GLubyte)imagedata[j * width_W * 3 + 3 * i];
//                img->mImageData[j][i][1] = (GLubyte)imagedata[j * width_W * 3 + 3 * i + 1];
//                img->mImageData[j][i][2] = (GLubyte)imagedata[j * width_W * 3 + 3 * i + 2];
//            }
//        }
    }

    if(x == 0 && y == 0 && xx == 0 && yy == 0)
    {
        xx = img->mImageWidth - 1;
        yy = img->mImageLength - 1;
    }
    //cout<<"xx:"<<xx<<" yy:"<<yy<<endl;
    int width = xx -x + 1;
    int length = yy - y +1;

    if(width <= 0 || length <= 0)
    {
        cout<<"The image you choose is not valid! The width and length must be greater than 0;"<<endl;
        return;
    }
    else if (x < 0|| y < 0|| xx >= img->mImageWidth || yy >= img->mImageLength)
    {
        cout<<"The coordinates goes out of the scope!";
        return;
    }

    if(filename.compare(filename.length() - 4, 4,".tif") != 0)
    {
        filename.append(".tif");
    }

    mFile.open(filename.c_str());

    if(!mFile)
    {
        printf("Can not open file!\n");
        return;
    }

    write((short)img->header.tiff_endian);
    write((short)img->header.tiff_magic);
    if(img->mPhotoMetric == 2)//RGB photo
    {
        write((int)(width * length * 3 + 8)); //header is 8 bytes.
        for(int i = img->mImageLength - yy -1; i <= img->mImageLength - y -1; i++)
        {
            for(int j = x; j <= xx; j++)
            {
                //cout<<i<<","<<j<<endl;
                mFile.write((char *)&(img->mImageData[i][j][0]), 1);
                mFile.write((char *)&(img->mImageData[i][j][1]), 1);
                mFile.write((char *)&(img->mImageData[i][j][2]), 1);
            }
        }
        write((short)12);
        write((short)256);
        write((short)4);
        write((int)1);
        write((int)width);
        write((short)257);
        write((short)4);
        write((int)1);
        write((int)length);
        write((short)258);
        write((short)3);
        write((int)3);
        write((int)length * width*3 + 8 +150);//150 = 12*12 +2 + 4 //12 entries + count + 4 bytes of 0
        write((short)259);
        write((short)3);
        write((int)1);
        write((short)img->mCompressed);
        write((short)0);
        write((short)262);
        write((short)3);
        write((int)1);
        write((short)img->mPhotoMetric);
        write((short)0);
        write((short)273);
        write((short)4);
        write((int)1);
        write((int)8);
        write((short)277);
        write((short)3);
        write((int)1);
        write((short)img->mSamplePerPixel);
        write((short)0);
        write((short)278);
        write((short)4);
        write((int)1);
        write((int)length);
        write((short)279);
        write((short)4);
        write((int)1);
        write((int)length * width * 3);
        write((short)282);
        write((short)5);
        write((int)1);
        write((int)length * width*3 + 8 + 150 + 2 * 3);
        write((short)283);
        write((short)5);
        write((int)1);
        write((int)length * width*3 + 8 + 150 + 2 * 3 + 8);
        write((short)296);
        write((short)3);
        write((int)1);
        write((short)img->mResolutionUnit);
        write((short)0);

        write((int)0); // 4 bytes of 0
        write((short)8);
        write((short)8);
        write((short)8);
        write((long long)img->mXResolution);
        write((long long)img->mYResolution);
    }
    else
    {
        write((int)(width * length + 8)); //header is 8 bytes.
        for(int i = img->mImageLength - yy -1; i <= img->mImageLength - y -1; i++)
        {
            for(int j = x; j <= xx; j++)
            {
                //cout<<i<<","<<j<<endl;
                mFile.write((char *)&(img->mImageData[i][j][0]), 1);
            }
        }
        write((short)11);
        write((short)256);
        write((short)4);
        write((int)1);
        write((int)width);
        write((short)257);
        write((short)4);
        write((int)1);
        write((int)length);
        write((short)258);
        write((short)3);
        write((int)1);
        write((short)img->mBitsPerSample);
        write((short)0);
        write((short)259);
        write((short)3);
        write((int)1);
        write((short)img->mCompressed);
        write((short)0);
        write((short)262);
        write((short)3);
        write((int)1);
        write((short)img->mPhotoMetric);
        write((short)0);
        write((short)273);
        write((short)4);
        write((int)1);
        write((int)8);
        write((short)278);
        write((short)4);
        write((int)1);
        write((int)length);
        write((short)279);
        write((short)4);
        write((int)1);
        write((int)length * width);
        write((short)282);
        write((short)5);
        write((int)1);
        write((int)length * width + 8 + 138);//138 = 11*12 + 2 + 4
        write((short)283);
        write((short)5);
        write((int)1);
        write((int)length * width + 8 + 138 + 8);
        write((short)296);
        write((short)3);
        write((int)1);
        write((short)img->mResolutionUnit);
        write((short)0);

        write((int)0); // 4 bytes of 0
        write((short)8);
        write((short)8);
        write((short)8);
        write((long long)img->mXResolution);
        write((long long)img->mYResolution);

    }
    mFile.close();
}

template <class T>
void TiffWrite::write(T obj)
{
    if(img->mEndian_Convert)
        endianswap(&obj);
    mFile.write((char *)&obj, sizeof(T));
}
