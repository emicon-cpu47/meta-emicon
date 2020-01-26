# TODO: ltp-ddt fails to build with linaro gcc 4.9
# remove this bbappend when fixed

ARAGO_TEST_remove_varsomam33 ="\
    mtd-utils-ubifs-tests \
"

ARAGO_TI_TEST_remove_varsomam33 = "\
    ltp-ddt \
    "

ARAGO_TI_TEST_remove_varsomam43 = "\
    ltp-ddt \
    "

ARAGO_TI_TEST_remove_emcpu47 = "\
    ltp-ddt \
    "

ARAGO_TEST_remove_emcpu47 ="\
    mtd-utils-ubifs-tests \
"

ARAGO_TI_TEST_remove_emcpu47n1g = "\
    ltp-ddt \
    "

ARAGO_TEST_remove_emcpu47n1g ="\
    mtd-utils-ubifs-tests \
"

ARAGO_TI_TEST_remove_emcpu47n1g2 = "\
    ltp-ddt \
    "

ARAGO_TEST_remove_emcpu47n1g2 ="\
    mtd-utils-ubifs-tests \
"