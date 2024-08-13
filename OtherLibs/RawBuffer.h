#ifndef _RAW_BUFFER_H_
#define _RAW_BUFFER_H_

#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

#define RAWBUFFER_ERR_PUSHLENGTH_NEGETIVE 						-1
#define RAWBUFFER_ERR_PUSHLENGTH_BIGGER_THAN_BUFFER_SIZE 		-2
#define RAWBUFFER_ERR_PULLLENGTH_BIGGER_THAN_REMAIN_DATA_SIZE 	-3

typedef struct RawBuffer_ {
	int BufLength;
	int Variety;
	int Readers;
	int ERR;
	/** داده با دستور malloc تعریف شده و میتواند هر طولی داشته باشد. */
	uint8_t* Data;
	/** تعداد خانه های حافظه نوشته شده در بافر */
	int Wrtn[1];
	/** تعداد خانه های حافظه خوانده شده توسط خوانندگان مختلف از بافر */
	#define rbREADERS 2
	int Read[rbREADERS];

	//Due to unknown error, every element defined here may overlap structure arrays in NO_MALLOC condition!!! (mingw compiler)
} RawBuffer;



/**
 * حافظه عمومی کلاس را ورودی میگیرد
 *
 * @param[in,Out] mRB حافظه عمومی کلاس
 * @param[in] BufLength_ طول بافر
 * @param[in] Variety_ تعداد بایت قابل ذخیره در هر خانه حافظه
 * @param[in] ptr_Data اشاره گر داده
 */
void InitRawBuffer(RawBuffer* mRB, int BufLength_, int Variety_, uint8_t ptr_Data[]);


/**
 * حافظه بافر را آزاد می کند.
 *
 * @param[in] mRB حافظه عمومی کلاس
 */
void rbErase(RawBuffer* mRB);

/**
 * حافظه بافر را پاک می کند.
 *
 * @param[in] mRB حافظه عمومی کلاس
 */
void rbReset(RawBuffer* mRB);



/**
 * تعداد خانه های حافظه خوانده نشده را باز میگرداند.
 *
 * @param[in] mRB حافظه عمومی کلاس
 * @param[in] reader شماره خواننده، شروع از صفر
 * @return تعداد خانه های حافظه خوانده نشده
 */
int rbGetRemainLength(RawBuffer* mRB, int reader);

/**
 * چند خانه حافظه را با رشته داده ورودی پر می کند.
 * نباید طول داده ورودی از طول بافر بیشتر باشد
 *
 * @param[in] mRB حافظه عمومی کلاس
 * @param[in] what داده ورودی از چه نوعی است و کجای خانه های حافظه را اشغال می کند، شروع از یک
 * @param[in] PushData رشته داده ورودی
 * @param[in] PushLength طول داده ورودی
 */

/**
 * تعداد خانه های حافظه خوانده نشده قبل از یک کاراکتر خاص را باز میگرداند.
 *
 * @param[in] mRB حافظه عمومی کلاس
 * @param[in] reader شماره خواننده، شروع از صفر
 * @return تعداد خانه های حافظه خوانده نشده یا 1- در صورت خطا
 */
int rbGetRemainLengthBeforeChar(RawBuffer* mRB, uint8_t special_char, int len, int reader);


void rbPush(RawBuffer* mRB, int what, uint8_t* PushData, int PushLength);

/**
 * چند خانه پر شده را دوباره پر می کند.
 * معمولا برای پر کردن خانه های حافظه با بیش از یک بایت داده، پس از rbPush از این دستور استفاده می شود.
 *
 * @param[in] mRB حافظه عمومی کلاس
 * @param[in] what داده ورودی از چه نوعی است و کجای خانه های حافظه را اشغال می کند، شروع از یک
 * @param[in] PushData رشته داده ورودی
 * @param[in] PushLength طول داده ورودی
 */
void rbRePush(RawBuffer* mRB, int what, uint8_t* PushData, int PushLength);

/**
 * رشته داده ورودی را با چند خانه حافظه پر می کند.
 *
 * @param[in] mRB حافظه عمومی کلاس
 * @param[in] what داده درخواستی از چه نوعی است و کجای خانه های حافظه را اشغال می کند، شروع از یک
 * @param[out] PullData رشته داده خروجی
 * @param[in] maxPullLength بیشینه طول درخواستی که در صورت وجود داده می شود.
 * @param[in] reader شماره خواننده، شروع از صفر
 * @return طول واقعی خوانده شده
 */
int rbPull(RawBuffer* mRB, int what, uint8_t* PullData, int maxPullLength, int reader);

/**
 * رشته داده ورودی را با چند خانه حافظه که از قبل خوانده شده پر می کند.
 * معمولا برای خواندن بیش از یک بایت از خانه های حافظه، پس از rbPull از این دستور استفاده می شود
 * نکته مهم هنگام استفاده از این تابع این است که باید طول خروجی از rbPull به آن ورودی داده شود نه طول ورودی به rbPull
 *
 * @param[in] mRB حافظه عمومی کلاس
 * @param[in] what داده درخواستی از چه نوعی است و کجای خانه های حافظه را اشغال می کند، شروع از یک
 * @param[out] PullData رشته داده خروجی
 * @param[in] PullLength بیشینه طول درخواستی که در صورت وجود داده می شود.
 * @param[in] reader شماره خواننده، شروع از صفر
 * @return طول خوانده شده
 */
int rbRePull(RawBuffer* mRB, int what, uint8_t* PullData, int PullLength, int reader);

#ifdef __cplusplus
}
#endif

#endif  //_NSRRAWBUFFER3_H_
