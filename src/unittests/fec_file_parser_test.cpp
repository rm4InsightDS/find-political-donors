#include <fec_file_parser.h>
#include <iostream>
#include <sstream>
#include <cassert>
#include <vector>
#include <functional>
#include <string>

using std::cout;
using std::endl;
using sstream = std::stringstream;
using std::vector;
using std::function;
using std::string;

struct UnitTest {
    string name;
    function<bool()> testBody;
};


int
main (int argc, char *argv[]) {

    vector<UnitTest> unittests;
    unittests.push_back( UnitTest {"Simple test", [&]() -> bool {
        sstream ss;
        ss << "C00177436|N|M2|P|201702039042410894|15|IND|DEEHAN, WILLIAM N|"
        "ALPHARETTA|GA|300047357|UNUM|SVP, SALES, CL|01312017|384||"
        "PR2283873845050|1147350||P/R DEDUCTION ($192.00 BI-WEEKLY)|4020820171370029337";
        FecFileParser fecParser {&ss};
        auto recordsBlock = fecParser.getNextRecordsBlock();
        if ( !fecParser.isEof() ) return false;
        if ( recordsBlock.size() != 1 ) return false;
        if ( recordsBlock[0].CMTE_ID != "C00177436" ) return false;
        if ( recordsBlock[0].ZIP_CODE != "30004" ) return false;
        if ( recordsBlock[0].TRANSACTION_DT.YEAR != 2017 ) return false;
        if ( recordsBlock[0].TRANSACTION_DT.MONTH != 1 ) return false;
        if ( recordsBlock[0].TRANSACTION_DT.DAY != 31 ) return false;
        if ( recordsBlock[0].TRANSACTION_AMT != 384 ) return false;
        return true;

    }});

    unittests.push_back( UnitTest {"Empty TRANSACTION_DT", [&]() -> bool {
        sstream ss;
        ss << "C00177436|N|M2|P|201702039042410894|15|IND|DEEHAN, WILLIAM N|ALPHARETTA|GA|300047357|UNUM|SVP, SALES, CL||384||PR2283873845050|1147350||P/R DEDUCTION ($192.00 BI-WEEKLY)|4020820171370029337";
        FecFileParser fecParser {&ss};
        auto recordsBlock = fecParser.getNextRecordsBlock();
        if ( !fecParser.isEof() ) return false;
        if ( recordsBlock.size() != 1 ) return false;
        if ( recordsBlock[0].CMTE_ID != "C00177436" ) return false;
        if ( recordsBlock[0].ZIP_CODE != "30004" ) return false;
        if ( recordsBlock[0].TRANSACTION_DT.YEAR != 0 ) return false;
        if ( recordsBlock[0].TRANSACTION_DT.MONTH != 0 ) return false;
        if ( recordsBlock[0].TRANSACTION_DT.DAY != 0 ) return false;
        if ( recordsBlock[0].TRANSACTION_AMT != 384 ) return false;
        return true;

    }});

    unittests.push_back( UnitTest {"Malformed TRANSACTION_DT", [&]() -> bool {
        sstream ss;
        ss <<
R"(C00177436|N|M2|P|201702039042410894|15|IND|DEEHAN, WILLIAM N|ALPHARETTA|GA|300047357|UNUM|SVP, SALES, CL|01322017|384||PR2283873845050|1147350||P/R DEDUCTION ($192.00 BI-WEEKLY)|4020820171370029337
C00177436|N|M2|P|201702039042410894|15|IND|DEEHAN, WILLIAM N|ALPHARETTA|GA|300047357|UNUM|SVP, SALES, CL|00312017|384||PR2283873845050|1147350||P/R DEDUCTION ($192.00 BI-WEEKLY)|4020820171370029337
C00177436|N|M2|P|201702039042410894|15|IND|DEEHAN, WILLIAM N|ALPHARETTA|GA|300047357|UNUM|SVP, SALES, CL|02312017|384||PR2283873845050|1147350||P/R DEDUCTION ($192.00 BI-WEEKLY)|4020820171370029337
C00177436|N|M2|P|201702039042410894|15|IND|DEEHAN, WILLIAM N|ALPHARETTA|GA|300047357|UNUM|SVP, SALES, CL|02292017|384||PR2283873845050|1147350||P/R DEDUCTION ($192.00 BI-WEEKLY)|4020820171370029337
C00177436|N|M2|P|201702039042410894|15|IND|DEEHAN, WILLIAM N|ALPHARETTA|GA|300047357|UNUM|SVP, SALES, CL|06312017|384||PR2283873845050|1147350||P/R DEDUCTION ($192.00 BI-WEEKLY)|4020820171370029337
C00177436|N|M2|P|201702039042410894|15|IND|DEEHAN, WILLIAM N|ALPHARETTA|GA|300047357|UNUM|SVP, SALES, CL|13312017|384||PR2283873845050|1147350||P/R DEDUCTION ($192.00 BI-WEEKLY)|4020820171370029337
)";
        FecFileParser fecParser {&ss};
        auto recordsBlock = fecParser.getNextRecordsBlock();
        if ( !fecParser.isEof() ) return false;
        if ( recordsBlock.size() != 6 ) return false;
        for (auto&& record : recordsBlock) {
            if ( record.CMTE_ID != "C00177436" ) return false;
            if ( record.ZIP_CODE != "30004" ) return false;
            if ( record.TRANSACTION_DT.YEAR != 0 ) return false;
            if ( record.TRANSACTION_DT.MONTH != 0 ) return false;
            if ( record.TRANSACTION_DT.DAY != 0 ) return false;
            if ( record.TRANSACTION_AMT != 384 ) return false;
        }
        return true;

    }});

    unittests.push_back( UnitTest {"Well-formed TRANSACTION_DT", [&]() -> bool {
        sstream ss;
        ss <<
R"(C00177436|N|M2|P|201702039042410894|15|IND|DEEHAN, WILLIAM N|ALPHARETTA|GA|300047357|UNUM|SVP, SALES, CL|01322017|384||PR2283873845050|1147350||P/R DEDUCTION ($192.00 BI-WEEKLY)|4020820171370029337
C00177436|N|M2|P|201702039042410894|15|IND|DEEHAN, WILLIAM N|ALPHARETTA|GA|300047357|UNUM|SVP, SALES, CL|01312017|384||PR2283873845050|1147350||P/R DEDUCTION ($192.00 BI-WEEKLY)|4020820171370029337
C00177436|N|M2|P|201702039042410894|15|IND|DEEHAN, WILLIAM N|ALPHARETTA|GA|300047357|UNUM|SVP, SALES, CL|12312017|384||PR2283873845050|1147350||P/R DEDUCTION ($192.00 BI-WEEKLY)|4020820171370029337
C00177436|N|M2|P|201702039042410894|15|IND|DEEHAN, WILLIAM N|ALPHARETTA|GA|300047357|UNUM|SVP, SALES, CL|02292016|384||PR2283873845050|1147350||P/R DEDUCTION ($192.00 BI-WEEKLY)|4020820171370029337
C00177436|N|M2|P|201702039042410894|15|IND|DEEHAN, WILLIAM N|ALPHARETTA|GA|300047357|UNUM|SVP, SALES, CL|07312017|384||PR2283873845050|1147350||P/R DEDUCTION ($192.00 BI-WEEKLY)|4020820171370029337
C00177436|N|M2|P|201702039042410894|15|IND|DEEHAN, WILLIAM N|ALPHARETTA|GA|300047357|UNUM|SVP, SALES, CL|08312017|384||PR2283873845050|1147350||P/R DEDUCTION ($192.00 BI-WEEKLY)|4020820171370029337
)";
        FecFileParser fecParser {&ss};
        auto recordsBlock = fecParser.getNextRecordsBlock();
        if ( !fecParser.isEof() ) return false;
        if ( recordsBlock.size() != 6 ) return false;
        return true;

    }});

    unittests.push_back( UnitTest {"Non-empty OtherId", [&]() -> bool {
        sstream ss;
        ss << "C00629618|N|TER|P|201701230300133512|15C|IND|PEREZ, JOHN A|"
        "LOS ANGELES|CA|90017|PRINCIPAL|DOUBLE NICKEL ADVISORS|01032017|"
        "40|H6CA34245|SA01251735122|1141239|||2012520171368850783";
        FecFileParser fecParser {&ss};
        auto recordsBlock = fecParser.getNextRecordsBlock();
        if ( !fecParser.isEof() ) return false;
        if ( !recordsBlock.empty() ) return false;
        return true;
    }});


    unittests.push_back( UnitTest {"Empty CMTE_ID", [&]() -> bool {
        sstream ss;
        ss << "|N|M2|P|201702039042410894|15|IND|DEEHAN, WILLIAM N|ALPHARETTA|GA|300047357|UNUM|SVP, SALES, CL|01312017|384||PR2283873845050|1147350||P/R DEDUCTION ($192.00 BI-WEEKLY)|4020820171370029337";
        FecFileParser fecParser {&ss};
        auto recordsBlock = fecParser.getNextRecordsBlock();
        if ( !fecParser.isEof() ) return false;
        if ( recordsBlock.size() != 0 ) return false;
        return true;

    }});

    unittests.push_back( UnitTest {"Empty TRANSACTION_AMT", [&]() -> bool {
        sstream ss;
        ss << "C00177436|N|M2|P|201702039042410894|15|IND|DEEHAN, WILLIAM N|ALPHARETTA|GA|300047357|UNUM|SVP, SALES, CL|01312017|||PR2283873845050|1147350||P/R DEDUCTION ($192.00 BI-WEEKLY)|4020820171370029337";
        FecFileParser fecParser {&ss};
        auto recordsBlock = fecParser.getNextRecordsBlock();
        if ( !fecParser.isEof() ) return false;
        if ( recordsBlock.size() != 0 ) return false;
        return true;

    }});

    unittests.push_back( UnitTest {"Empty TRANSACTION_DT", [&]() -> bool {
        sstream ss;
        ss << "C00177436|N|M2|P|201702039042410894|15|IND|DEEHAN, WILLIAM N|ALPHARETTA|GA|300047357|UNUM|SVP, SALES, CL||384||PR2283873845050|1147350||P/R DEDUCTION ($192.00 BI-WEEKLY)|4020820171370029337";
        FecFileParser fecParser {&ss};
        auto recordsBlock = fecParser.getNextRecordsBlock();
        if ( !fecParser.isEof() ) return false;
        if ( recordsBlock.size() != 1 ) return false;
        if ( recordsBlock[0].CMTE_ID != "C00177436" ) return false;
        if ( recordsBlock[0].ZIP_CODE != "30004" ) return false;
        if ( recordsBlock[0].TRANSACTION_DT.YEAR != 0 ) return false;
        if ( recordsBlock[0].TRANSACTION_DT.MONTH != 0 ) return false;
        if ( recordsBlock[0].TRANSACTION_DT.DAY != 0 ) return false;
        if ( recordsBlock[0].TRANSACTION_AMT != 384 ) return false;
        return true;
    }});


    unittests.push_back( UnitTest {"List of records", [&]() -> bool {
        sstream ss;
        ss <<
R"(C00629618|N|TER|P|201701230300133512|15C|IND|PEREZ, JOHN A|LOS ANGELES|CA|90017|PRINCIPAL|DOUBLE NICKEL ADVISORS|01032017|40|H6CA34245|SA01251735122|1141239|||2012520171368850783
C00177436|N|M2|P|201702039042410894|15|IND|DEEHAN, WILLIAM N|ALPHARETTA|GA|300047357|UNUM|SVP, SALES, CL|01312017|384||PR2283873845050|1147350||P/R DEDUCTION ($192.00 BI-WEEKLY)|4020820171370029337
C00384818|N|M2|P|201702039042412112|15|IND|ABBOTT, JOSEPH|WOONSOCKET|RI|028956146|CVS HEALTH|VP, RETAIL PHARMACY OPS|01122017|250||2017020211435-887|1147467|||4020820171370030285
C00177436|N|M2|P|201702039042410893|15|IND|SABOURIN, JAMES|LOOKOUT MOUNTAIN|GA|307502818|UNUM|SVP, CORPORATE COMMUNICATIONS|01312017|230||PR1890575345050|1147350||P/R DEDUCTION ($115.00 BI-WEEKLY)|4020820171370029335
C00177436|N|M2|P|201702039042410895|15|IND|JEROME, CHRISTOPHER|FALMOUTH|ME|041051896|UNUM|EVP, GLOBAL SERVICES|01312017|384||PR2283905245050|1147350||P/R DEDUCTION ($192.00 BI-WEEKLY)|4020820171370029342
C00384818|N|M2|P|201702039042412112|15|IND|BAKER, SCOTT|WOONSOCKET|RI|028956146|CVS HEALTH|EVP, HEAD OF RETAIL OPERATIONS|01122017|333||2017020211435-910|1147467|||4020820171370030287
C00177436|N|M2|P|201702039042410894|15|IND|FOLEY, JOSEPH|FALMOUTH|ME|041051935|UNUM|SVP, CORP MKTG & PUBLIC RELAT.|01312017|384||PR2283904845050|1147350||P/R DEDUCTION ($192.00 BI-WEEKLY)|4020820171370029339
)";
        FecFileParser fecParser {&ss};
        auto recordsBlock = fecParser.getNextRecordsBlock();
        if ( !fecParser.isEof() ) return false;
        if ( recordsBlock.size() != 6 ) return false;
        if ( recordsBlock[0].CMTE_ID != "C00177436" ) return false;
        if ( recordsBlock[0].ZIP_CODE != "30004" ) return false;
        if ( recordsBlock[0].TRANSACTION_DT.YEAR != 2017 ) return false;
        if ( recordsBlock[0].TRANSACTION_DT.MONTH != 1 ) return false;
        if ( recordsBlock[0].TRANSACTION_DT.DAY != 31 ) return false;
        if ( recordsBlock[0].TRANSACTION_AMT != 384 ) return false;
        if ( recordsBlock[1].CMTE_ID != "C00384818" ) return false;
        if ( recordsBlock[1].ZIP_CODE != "02895" ) return false;
        if ( recordsBlock[1].TRANSACTION_DT.YEAR != 2017 ) return false;
        if ( recordsBlock[1].TRANSACTION_DT.MONTH != 1 ) return false;
        if ( recordsBlock[1].TRANSACTION_DT.DAY != 12 ) return false;
        if ( recordsBlock[1].TRANSACTION_AMT != 250 ) return false;
        if ( recordsBlock[2].CMTE_ID != "C00177436" ) return false;
        if ( recordsBlock[2].ZIP_CODE != "30750" ) return false;
        if ( recordsBlock[2].TRANSACTION_DT.YEAR != 2017 ) return false;
        if ( recordsBlock[2].TRANSACTION_DT.MONTH != 1 ) return false;
        if ( recordsBlock[2].TRANSACTION_DT.DAY != 31 ) return false;
        if ( recordsBlock[2].TRANSACTION_AMT != 230 ) return false;
        if ( recordsBlock[3].CMTE_ID != "C00177436" ) return false;
        if ( recordsBlock[3].ZIP_CODE != "04105" ) return false;
        if ( recordsBlock[3].TRANSACTION_DT.YEAR != 2017 ) return false;
        if ( recordsBlock[3].TRANSACTION_DT.MONTH != 1 ) return false;
        if ( recordsBlock[3].TRANSACTION_DT.DAY != 31 ) return false;
        if ( recordsBlock[3].TRANSACTION_AMT != 384 ) return false;
        if ( recordsBlock[4].CMTE_ID != "C00384818" ) return false;
        if ( recordsBlock[4].ZIP_CODE != "02895" ) return false;
        if ( recordsBlock[4].TRANSACTION_DT.YEAR != 2017 ) return false;
        if ( recordsBlock[4].TRANSACTION_DT.MONTH != 1 ) return false;
        if ( recordsBlock[4].TRANSACTION_DT.DAY != 12 ) return false;
        if ( recordsBlock[4].TRANSACTION_AMT != 333 ) return false;
        if ( recordsBlock[5].CMTE_ID != "C00177436" ) return false;
        if ( recordsBlock[5].ZIP_CODE != "04105" ) return false;
        if ( recordsBlock[5].TRANSACTION_DT.YEAR != 2017 ) return false;
        if ( recordsBlock[5].TRANSACTION_DT.MONTH != 1 ) return false;
        if ( recordsBlock[5].TRANSACTION_DT.DAY != 31 ) return false;
        if ( recordsBlock[5].TRANSACTION_AMT != 384 ) return false;
        return true;
    }});


    cout << "1.." << unittests.size() << endl;
    int retcode = 0;
    for (size_t i = 0; i < unittests.size(); ++i) {
        if (unittests[i].testBody()) {
            cout << "ok " << i+1 << " - " << unittests[i].name << endl;
        } else {
            cout << "not ok " << i+1 << " - " << unittests[i].name << endl;
            retcode = 1;
        }

    }
    exit( retcode );
}
