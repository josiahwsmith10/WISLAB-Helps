
#ifndef INI_FILE_H_
#define INI_FILE_H_

#define int32_t  int
#define int8_t	 char
#define float32_t	float
#define float64_t	double
#ifdef __cplusplus
extern "C"
{

#endif

	#define MAX_INI_SIZE (1024*16)

	extern void reset_write_ini();
	extern int32_t load_read_ini(int8_t *pinidata,int32_t size);
	extern int32_t get_write_ini(int8_t *pinidata,int32_t *size);
	extern int32_t read_profile_int( const int8_t *section, const int8_t *key,int32_t default_value);
	extern float32_t read_profile_float( const int8_t *section, const int8_t *key,float32_t default_value);
	extern int32_t write_profile_int( const int8_t *section, const int8_t *key,int32_t value);
	extern int32_t write_profile_float( const int8_t *section, const int8_t *key,float32_t value);
	int32_t write_profile_string(const int8_t *section,const int8_t *key,const int8_t *value);
	extern int32_t write_profile_section( const int8_t *section);


#ifdef __cplusplus
}; //end of extern "C" {
#endif

#endif //end of INI_FILE_H_

