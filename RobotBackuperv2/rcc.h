// -*- C++ -*-
#if !defined( RCC_H__)
#define RCC_H__

///////////////////////////////////////////////////////////////
//
//                 Simple & friendly
//             K a w a s a k i   R o b o t
//
//    Copyright (C) 2001,2002,2003,2004,2005,2006 By
//         System Technology Development Center,
//             Kawasaki Heavy Industries, LTD.
//
//    This software is furnished under a license and may be used
//    and copied only in accordance with the terms of such license
//    and with the inclusion of the above copyright notice.
//
///////////////////////////////////////////////////////////////

/*!
 \file  rcc.h
 \brief  Kawasaki `Robot Control Class` Library
 \author Akiyoshi Saiki
 \version 2.0
*/

#include <exception>
#include <string>
#include "trans.h"

namespace KRcc
{

/*!
 * \brief アームに対するインターフェースを提供する
 */
class CArm
{
    friend class CRobot;
    friend class CRobotImpl;
    CArm& operator=( const CArm& );	//!< 代入禁止

#ifndef DOXYGEN_ONLY
    // Handle-Body Idiom
    struct { void* padding[2]; } p_body;
#else
    class CArmImpl *p_body;
#endif

 public:
    //! コンストラクタ
    CArm( const char * arm_type );
    CArm( const CArm& r );        //!< コピー

    //! デストラクタ
    ~CArm();

    //! アーム名称
    const char* name() const;

    //! ツール設定
    void tool( const CTrans& t );
    //! ベース座標設定
    void base( const CTrans& b );
    //! ツール変換値取得
    const CTrans &tool(void) const;
    //! ベース座標値取得
    const CTrans &base(void) const;
    
    int  error() const;		//! 順逆変換のエラーコード
    bool enable_throw( bool );	//! 逆変換時の例外を throw する／しないの選択

    //! 順変換
    CTrans point( const CJoint& ) const;

    //! 逆変換：参照姿勢と形態を指定：
    CJoint point( const CTrans&, const CJoint &ref, int conf ) const;

    //! 逆変換：参照姿勢を指定：形態は ref から計算
    CJoint point( const CTrans& tr, const CJoint &ref ) const;

    //! 逆変換：手首均分補間
    CJoint hybrid( const CTrans& xyz, const CJoint &jt456,
		   const CJoint &ref ) const;

    //! 各軸値から形態を判定
    int config( const CJoint &jt ) const;

    size_t  num_jt() const;                   //!< 外部軸を含まない軸数
};

/*!
 * \brief  通信に関するインターフェースを提供する
 */
class CCommu
{
    friend class CRobot;
    CCommu& operator=( const CCommu& );	//!< 代入禁止

#ifndef DOXYGEN_ONLY
    // Handle-Body Idiom
    struct { void* padding[2]; } p_body;
#else
    class CCommuImpl *p_body;
#endif

 public:
    CCommu( const char *cmmu_port = NULL );
    CCommu( const CCommu & );
    virtual ~CCommu();

    //! 通信ポート名称
    const char* name() const;

    //! コントローラへの接続処理：1XA,TCP,Serial
    bool connect( const char *commu_type );
    bool disconnect();

    //! モニタコマンドを実行
    int command( const char *cmd,  char *buf, size_t sz, int tmo = 500 );
    //! モニタコマンドを実行
    int command( const char *cmd, std::string &resp, int tmo = 500 /*msec*/ );
    //! モニタコマンドを実行
    int command( const char *cmd, int tmo = 500 /*msec*/ );

    //! ＡＳプログラムをコントローラにLoad
    int load( const char *fname, const char *qual = NULL );

    //! ＡＳプログラムをホストにSave
    int save( const char *fname,
              const char *prog = NULL, const char *qual = NULL );

    // save/load の callback
    virtual void callbackProgress( long cur, long total );
    virtual bool callbackInquiry( const std::string &as_msg, std::string &resp );
    const char *getLoadSaveMsg() const;

    //! 通信ログ開始
    bool startLog( const char *log_fname  );
    //! 通信ログ終了
    bool stopLog();

    int send( const char *p, unsigned sz );

    bool is_connected();
    void setTimeoutValue( unsigned int msec );
};


/*!
 * \brief CArm と CCommu を含む
 *
 */
class CRobot
{
#ifndef DOXYGEN_ONLY
    // Handle-Body Idiom
    struct { void* padding[2]; } p_body;
#else
    class CRobotImpl *p_body;
#endif

    CRobot& operator=( const CRobot& );	//!< 代入禁止

public:
    CRobot( const char * arm_, const char *comm_ = NULL);
    CRobot( const CRobot& r_ );   //!< コピー
    ~CRobot();

    CCommu &com();

    //! アーム名称
    const char* name() const;

    //! 順逆変換のエラーコード
    int  error() const;
    //! 逆変換時の例外を throw する／しないの選択
    bool enable_throw( bool b );

    //! ツール設定
    void tool( const CTrans& t );
    //! ベース座標設定
    void base( const CTrans& b );
    //! ツール変換値取得
    const CTrans &tool(void) const;
    //! ベース座標値取得
    const CTrans &base(void) const;

    //! 各軸値から形態を判定
    int config( const CJoint &jt ) const;
    //! 現在値の形態を取得
    int config() const;

    //! 順変換
    CTrans point( const CJoint& ) const;

    //! 逆変換：参照姿勢と形態を指定：
    CJoint point( const CTrans&, const CJoint &ref, int conf ) const;

    //! 逆変換：参照姿勢を指定：形態は ref から計算
    CJoint point( const CTrans& tr, const CJoint &ref ) const;
    //! 逆変換：形態を指定：参照姿勢は現在値
    CJoint point( const CTrans& tr, int conf ) const;
    //! 逆変換：参照姿勢と形態は現在値
    CJoint point( const CTrans& tr ) const;

    //! 逆変換：手首均分補間
    CJoint hybrid( const CTrans& xyz, const CJoint &jt456,
		   const CJoint &ref ) const;
    //! 逆変換：手首均分補間
    CJoint hybrid( const CTrans& xyz, const CJoint &jt456 ) const;

    // op. Instruction
    void lMove( const CTrans &tr );
    void lMove( const CJoint &jt );
    void jMove( const CTrans &tr );
    void jMove( const CJoint &jt );
    void xMove( const CTrans &tr, int sig );
    void xMove( const CJoint &jt, int sig );
    void jAppro( const CTrans&, double );
    void jAppro( const CJoint&, double );
    void lAppro( const CTrans&, double );
    void lAppro( const CJoint&, double );
    void jDepart( double );
    void lDepart( double );

    void c1Move( const CTrans & );
    void c1Move( const CJoint & );
    void c2Move( const CTrans & );
    void c2Move( const CJoint & );

    void call( const char * );

    void mBreak( bool sync=false );
    void accuracy( double n, bool always=0 );
    enum { PERCENT, MMPS, SEC };
    void speed( double n, int unit=PERCENT, bool always=false );
    void accel( double n, bool always=0 );
    void decel( double n, bool always=0 );
    
    void here( CTrans &tr );   //!< 現在値を変換値で取得
    void here( CJoint &tr );   //!< 現在値を各軸値で取得

    CJoint ulim() const;
    CJoint llim() const;
    CJoint jointSpeed() const;

    void ulim( const CJoint& );
    void llim( const CJoint& );
    void jointSpeed( const CJoint& );

    void add( const class CExtLinAxis& );	//!< 外部軸（直動軸）の設定
    void add( const class CExtRotAxis& );	//!< 外部軸（回転軸）の設定

    size_t  num_jt() const;        		//!< 外部軸を含む全軸数

    //! 仮想コントローラに実機の専用出力信号をマッピングする
    int defsig( const char *sig_name, int no );
};

/////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////

    //! 逆変換：エラーコード
enum { OutOfLoUsrlim = -852,  OutOfHiUsrlim = -853,  OutOfRange = -857 };
    //! 形態
enum { Righty=0, Above=0, Dwrist=0, Lefty=0x01, Below=0x02, Uwrist=0x04 };

    //! 形態の判定
inline bool isLefty( int conf )  { return ( conf & Lefty  ) != 0; }
inline bool isBelow( int conf )  { return ( conf & Below  ) != 0; }
inline bool isUWrist( int conf ) { return ( conf & Uwrist )!= 0;  }
inline bool isRighty( int conf ) { return !isLefty( conf );  }
inline bool isAbove( int conf )  { return !isBelow( conf );  }
inline bool isDWrist( int conf ) { return !isUWrist( conf ); }


//! RCC 全体のデバッグフラグ
extern long dbgFlag;
//! 対応アーム名のリスト "...\0...\0...\0\0"
extern const char* rccArmList;

/////////////////////////////////////////

/////////////////////////////////////////

/*!
 * \brief  外部軸 設定  抽象クラス
 */
class CExtAxis
{
    friend class CRobotImpl;
protected:
    double llim, ulim;
    double max_spd;

    // XYZ: リンク距離
    // OAT: 走行軸は移動方向、回転軸は回転軸方向
    CTrans matrix;

public:
    CExtAxis( double ulim, double llim, double max_spd );
    CExtAxis( const CExtAxis &);
    virtual ~CExtAxis();
    virtual CTrans vec( double val ) const = 0;
    CExtAxis &operator =( const CExtAxis & );
};

/*!
 * \brief  直動軸
 */
class CExtLinAxis : public CExtAxis
{
public:
    CExtLinAxis( double ulim, double llim, double max_spd )
      : CExtAxis( ulim, llim, max_spd ) {}
    ~CExtLinAxis();
    virtual CTrans vec( double val ) const;    // オフセット＋走行方向
};


/*!
 * \brief  回転軸
 */
class CExtRotAxis : public CExtAxis
{
public:
    CExtRotAxis( double ulim, double llim, double max_spd )
      : CExtAxis( ulim, llim, max_spd ) {}
    ~CExtRotAxis();
    virtual CTrans vec( double val ) const;   // オフセット＋回転ベクトル
};

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

/*!
 * \brief  ＡＳ変数式構文解析器
 *
 * 文字列で与えられた変換値演算式を処理する
 */
class CParser
{
    CParser( const CParser & );		//!< コピー禁止
    CParser& operator =( const CParser & );   //!< コピー禁止

    friend class CParserImpl;
    class CParserImpl *body;
    class CAsVar *as_var;

protected:
    //!代入文処理（ユーザ再定義可能）
    virtual const void* var_assign( int type, const char *, const void *p );
    //!変数参照処理（ユーザ再定義可能）
    virtual const void* var_ref( int type, const char * );

public:
    enum TMotionOpe {
        OP_Unkown = 0,
        OP_JMOVE, OP_LMOVE, OP_HMOVE, OP_C1MOVE, OP_C2MOVE,
        OP_JAPPRO, OP_LAPPRO,
        OP_JDEPART, OP_LDEPART,
        OP_JOINT, OP_LINEAR,
        OP_DRIVE,
        OP_DRAW, OP_TDRAW,
        OP_JWS, OP_LWS, OP_LWC, OP_LWE, OP_C1WC, OP_C2WC, OP_C2WE
    };
    enum  { Unkown=0, Trans=0x01, Joint=0x02, Real=0x04,  Motion=0x100 };
    struct answer
    {
        int    type;
        CTrans trans;
        CJoint joint;
        float  real;
        int    ope;       // TMotionOpe
    } answer;

    CParser();
    CParser( CRobot &robot );
    virtual ~CParser();

    void clear();

    int  parse( const char * );
    const char *getLastError() const;

    const CTrans& trans() const;    //!< 変換値を返す
    const CJoint& joint() const;    //!< 各軸値を返す
    float real() const;             //!< 実数値を返す

    friend std::istream& operator >>( std::istream&, CParser &);
};

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

/*
 * \brief 補間計算用 base クラス
 *
 * CIntJoint/CIntLinear/CIntCircular/CIntHybrid はこのクラスの派生
 */
class CInterpolation
{
protected:
    class CInterpolationImp *body;    //!< 補間計算の実態
    CInterpolation();
public:
    virtual ~CInterpolation();

    CInterpolation &operator()( double s );    //!< 補間係数の設定

    operator CJoint() const;    //!< 各軸値を返す
    operator CTrans() const;    //!< 変換値を返す
    double distance() const;
};

/*!
 * \brief 各軸補間
 */
class CIntJoint : public CInterpolation
{
    CIntJoint( const CIntJoint& );		  //!< コピー禁止
    CIntJoint &operator =( const CIntJoint& );    //!< 代入禁止
public:
    CIntJoint( const CJoint&, const CJoint& );
    CIntJoint( const CRobot&, const CJoint&, const CJoint& );
    virtual ~CIntJoint();
};

/*!
 * \brief 直線補間
 */
class CIntLinear : public CInterpolation
{
    CIntLinear( const CIntLinear& );              //!< コピー禁止
    CIntLinear &operator =( const CIntLinear& );  //!< 代入禁止
public:
    CIntLinear( const CTrans&, const CTrans& );
    CIntLinear( const CRobot&, const CJoint&, const CJoint& );
    virtual ~CIntLinear();
};

/*!
 * \brief 円弧補間
 */
class CIntCircular : public CInterpolation
{
    CIntCircular( const CIntCircular& );             //!< コピー禁止
    CIntCircular &operator =( const CIntCircular& ); //!< 代入禁止
public:
    CIntCircular( const CTrans&, const CTrans&, const CTrans&,
                  bool last_half = false );
    CIntCircular( const CRobot&, const CJoint&, const CJoint&, const CJoint&, 
                  bool last_half = false );
    virtual ~CIntCircular();
};

/*!
 * \brief 手首均分補間
 */
class CIntHybrid : public CInterpolation
{
    CIntHybrid( const CIntHybrid& );		    //!< コピー禁止
    CIntHybrid &operator =( const CIntHybrid& );    //!< 代入禁止
public:
    CIntHybrid( const CRobot&, const CJoint&, const CJoint& );
    virtual ~CIntHybrid();
};


/*!
 * \brief 円弧手首均分補間
 */
class CIntHybridCircular : public CInterpolation
{
    CIntHybridCircular( const CIntHybridCircular& );		    //!< コピー禁止
    CIntHybridCircular &operator =( const CIntHybridCircular& );    //!< 代入禁止
public:
    CIntHybridCircular( const CRobot&, const CJoint&, const CJoint&, const CJoint&,
                        bool last_half = false );
    virtual ~CIntHybridCircular();
};

/////////////////////////////////////////////////////////////


/*!
 * \brief RCC 例外処理
 */
class rcc_exception : public std::exception
{
#if defined(_MSC_VER)
public:
    rcc_exception( const char *s = "rcc exception" ) throw ()
		: std::exception( s ) {}
#else
    const char *ex_str;
public:
    rcc_exception( const char *s = "rcc exception" ) throw ()
		: ex_str(s) {}
    const char* what()  const throw() { return ex_str; }
#endif
};

/////////////////////////////////////////


} // namespace KRcc

#endif /* RCC_H */
