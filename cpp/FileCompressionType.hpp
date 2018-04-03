/*
 * Copyright (c) 2018 Snowflake Computing, Inc. All rights reserved.
 */

#ifndef SNOWFLAKECLIENT_FILECOMPRESSIONTYPE_HPP
#define SNOWFLAKECLIENT_FILECOMPRESSIONTYPE_HPP

#include <vector>
#include <string>

namespace Snowflake
{
namespace Client
{
/**
 * Compression types metadata
 */
class FileCompressionType
{
public:
  /**
   * enum of compression types
   */
  static const FileCompressionType GZIP;

  static const FileCompressionType DEFLATE;

  static const FileCompressionType RAW_DEFLATE;

  static const FileCompressionType BZIP2;

  static const FileCompressionType ZSTD;

  static const FileCompressionType BROTLI;

  static const FileCompressionType LZIP;

  static const FileCompressionType LZMA;

  static const FileCompressionType LZO;

  static const FileCompressionType XZ;

  static const FileCompressionType COMPRESS;

  static const FileCompressionType ORC;

  static const FileCompressionType PARQUET;

  /// special type indicating no compression type
  static const FileCompressionType NONE;

  static const std::vector<const FileCompressionType *> types;

  /**
   * Given file's full path, return its compression type
   * @param fileFullPath
   * @return
   */
  static const FileCompressionType * guessCompressionType(std::string &fileFullPath);

  /**
   * @return Compression type by looking up submime type;
   */
  static const FileCompressionType * lookUpBySubMime(const char * subMime);


  /**
   * @return true if compression type is supported by snowflake
   */
  bool getIsSupported() const;

  /**
   * @return file extension
   */
  const char * getFileExtension() const;

private:
  /**
   * @return true if match magic number otherwise false
   */
  bool matchMagicNumber(char * header) const;

  /**
   * @return true if match one of the sub mime types othewise false
   */
  bool matchSubMimeType(const char * subMime) const;

  /// private constructor to protect external initialization
  FileCompressionType(){}

  /// constrcut enum value
  FileCompressionType(const char * fileExtension,
                      bool isSupported);

  /// constrcut enum value
  FileCompressionType(const char * fileExtension,
                      std::vector<const char *> *magicNumbers,
                      short magicBytes,
                      bool isSupported);

  /// file extension
  const char * m_fileExtension;

  /// magic number to determine compression type
  //const unsigned char m_magicNumbers[];
  std::vector<const char *> *m_magicNumbers;

  /// magic bytes
  short m_magicBytes;
  //const char ** m_magicNumbers;

  /// sub mime type
  std::vector<const char *> m_subMimeTypes;

  /// whether compression type is supported or not
  bool m_isSupported;
};
} // Client
} // Snowflake


#endif //SNOWFLAKECLIENT_FILECOMPRESSIONTYPE_HPP
