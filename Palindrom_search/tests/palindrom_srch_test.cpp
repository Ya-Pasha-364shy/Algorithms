#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "sources/palindrom_srch.hpp"

using namespace fsm;

TEST(FSMTestW, SequenceEquality1) {
	fsm_palindrom_srch fsm1;

	/* 0/1 0/1 0/1 1/0
	 * построенная строка по заданной последовательности. */
	std::string text_by_fsm_sequence1 = "Test";
	std::vector<fsm_output_symbol_t> fsm_out_sequence;
	fsm1.fsm_orchestrator_states(text_by_fsm_sequence1);

	std::vector<fsm_output_symbol_t> expected_out_sequence = {
	                                                           NODE_STATUS_COMPLETED,
	                                                           NODE_STATUS_COMPLETED,
	                                                           NODE_STATUS_COMPLETED,
	                                                           NODE_STATUS_FAILED
	                                                         };

	fsm_out_sequence = fsm1.fsm_get_output_sequence();

	EXPECT_TRUE(fsm_out_sequence == expected_out_sequence);
}

TEST(FSMTestW, SequenceEquality2) {
	fsm_palindrom_srch fsm2;

	/* 0/1 0/1 0/1 1/0 2/0
	 * построенная строка по заданной последовательности. */
	std::string text_by_fsm_sequence2 = "Test ";
	std::vector<fsm_output_symbol_t> fsm_out_sequence;
	fsm2.fsm_orchestrator_states(text_by_fsm_sequence2);

	std::vector<fsm_output_symbol_t> expected_out_sequence = {
	                                                           NODE_STATUS_COMPLETED,
	                                                           NODE_STATUS_COMPLETED,
	                                                           NODE_STATUS_COMPLETED,
	                                                           NODE_STATUS_FAILED,
	                                                           NODE_STATUS_FAILED
	                                                         };

	fsm_out_sequence = fsm2.fsm_get_output_sequence();

	EXPECT_TRUE(fsm_out_sequence == expected_out_sequence);
}

TEST(FSMTestW, SequenceEquality3) {
	fsm_palindrom_srch fsm3;

	/* 0/1 0/1 1/0 2/0
	 * построенная строка по заданной последовательности. */
	std::string text_by_fsm_sequence3 = "Txt ";
	std::vector<fsm_output_symbol_t> fsm_out_sequence;
	fsm3.fsm_orchestrator_states(text_by_fsm_sequence3);

	std::vector<fsm_output_symbol_t> expected_out_sequence = {
	                                                           NODE_STATUS_COMPLETED,
	                                                           NODE_STATUS_COMPLETED,
	                                                           NODE_STATUS_FAILED,
	                                                           NODE_STATUS_COMPLETED
	                                                         };

	fsm_out_sequence = fsm3.fsm_get_output_sequence();

	EXPECT_TRUE(fsm_out_sequence == expected_out_sequence);
}

TEST(FSMTestW, SequenceEquality4) {
	fsm_palindrom_srch fsm4;

	/* 1/1 2/0
	 * построенная строка по заданной последовательности. */
	std::string text_by_fsm_sequence4 = "T ";
	std::vector<fsm_output_symbol_t> fsm_out_sequence;
	fsm4.fsm_orchestrator_states(text_by_fsm_sequence4);

	std::vector<fsm_output_symbol_t> expected_out_sequence = {
	                                                           NODE_STATUS_COMPLETED,
	                                                           NODE_STATUS_FAILED
	                                                         };

	fsm_out_sequence = fsm4.fsm_get_output_sequence();

	EXPECT_TRUE(fsm_out_sequence == expected_out_sequence);
}

TEST(FSMTestW, SequenceEquality5) {
	fsm_palindrom_srch fsm5;

	/* 2/0 2/0
	 * построенная строка по заданной последовательности. */
	std::string text_by_fsm_sequence5 = "  ";
	std::vector<fsm_output_symbol_t> fsm_out_sequence;
	fsm5.fsm_orchestrator_states(text_by_fsm_sequence5);

	std::vector<fsm_output_symbol_t> expected_out_sequence = {
	                                                           NODE_STATUS_FAILED,
	                                                           NODE_STATUS_FAILED
	                                                         };

	fsm_out_sequence = fsm5.fsm_get_output_sequence();

	EXPECT_TRUE(fsm_out_sequence == expected_out_sequence);
}

TEST(FSMTestW, SequenceEquality6) {
	fsm_palindrom_srch fsm6;

	/* 2/0 1/1 2/0
	 * построенная строка по заданной последовательности. */
	std::string text_by_fsm_sequence6 = " s ";
	std::vector<fsm_output_symbol_t> fsm_out_sequence;
	fsm6.fsm_orchestrator_states(text_by_fsm_sequence6);

	std::vector<fsm_output_symbol_t> expected_out_sequence = {
	                                                           NODE_STATUS_FAILED,
	                                                           NODE_STATUS_COMPLETED,
	                                                           NODE_STATUS_FAILED
	                                                         };

	fsm_out_sequence = fsm6.fsm_get_output_sequence();

	EXPECT_TRUE(fsm_out_sequence == expected_out_sequence);
}

TEST(FSMTestW, SequenceEquality7) {
	fsm_palindrom_srch fsm7;

	/* 0/1 0/1 1/0 2/1 1/1 2/0
	 * построенная строка по заданной последовательности. */
	std::string text_by_fsm_sequence7 = "Mom s ";
	std::vector<fsm_output_symbol_t> fsm_out_sequence;
	fsm7.fsm_orchestrator_states(text_by_fsm_sequence7);

	std::vector<fsm_output_symbol_t> expected_out_sequence = {
	                                                           NODE_STATUS_COMPLETED,
	                                                           NODE_STATUS_COMPLETED,
	                                                           NODE_STATUS_FAILED,
	                                                           NODE_STATUS_COMPLETED,
	                                                           NODE_STATUS_COMPLETED,
	                                                           NODE_STATUS_FAILED
	                                                         };

	fsm_out_sequence = fsm7.fsm_get_output_sequence();

	EXPECT_TRUE(fsm_out_sequence == expected_out_sequence);
}

TEST(FSMTestW, SequenceEquality8) {
	fsm_palindrom_srch fsm8;

	/* 0/1 0/1 1/0 0/1 1/1 2/0
	 * построенная строка по заданной последовательности. */
	std::string text_by_fsm_sequence8 = "TST R ";
	std::vector<fsm_output_symbol_t> fsm_out_sequence;
	fsm8.fsm_orchestrator_states(text_by_fsm_sequence8);

	std::vector<fsm_output_symbol_t> expected_out_sequence = {
	                                                           NODE_STATUS_COMPLETED,
	                                                           NODE_STATUS_COMPLETED,
	                                                           NODE_STATUS_FAILED,
	                                                           NODE_STATUS_COMPLETED,
	                                                           NODE_STATUS_COMPLETED,
	                                                           NODE_STATUS_FAILED
	                                                         };

	fsm_out_sequence = fsm8.fsm_get_output_sequence();

	EXPECT_TRUE(fsm_out_sequence == expected_out_sequence);
}

TEST(FSMTestW, SequenceEquality9) {
	fsm_palindrom_srch fsm9;

	/* 0/1 0/1 1/0 1/1 1/1 2/0
	 * построенная строка по заданной последовательности. */
	std::string text_by_fsm_sequence9 = "MOM,I.";
	std::vector<fsm_output_symbol_t> fsm_out_sequence;
	fsm9.fsm_orchestrator_states(text_by_fsm_sequence9);

	std::vector<fsm_output_symbol_t> expected_out_sequence = {
	                                                           NODE_STATUS_COMPLETED,
	                                                           NODE_STATUS_COMPLETED,
	                                                           NODE_STATUS_FAILED,
	                                                           NODE_STATUS_COMPLETED,
	                                                           NODE_STATUS_COMPLETED,
	                                                           NODE_STATUS_FAILED
	                                                         };

	fsm_out_sequence = fsm9.fsm_get_output_sequence();

	EXPECT_TRUE(fsm_out_sequence == expected_out_sequence);
}

TEST(FSMTestW, SequenceEquality10) {
	fsm_palindrom_srch fsm10;

	/* 0/1 0/1 1/0 1/1 2/0
	 * построенная строка по заданной последовательности. */
	std::string text_by_fsm_sequence10 = "DED? ";
	std::vector<fsm_output_symbol_t> fsm_out_sequence;
	fsm10.fsm_orchestrator_states(text_by_fsm_sequence10);

	std::vector<fsm_output_symbol_t> expected_out_sequence = {
	                                                           NODE_STATUS_COMPLETED,
	                                                           NODE_STATUS_COMPLETED,
	                                                           NODE_STATUS_FAILED,
	                                                           NODE_STATUS_COMPLETED,
	                                                           NODE_STATUS_FAILED
	                                                         };

	fsm_out_sequence = fsm10.fsm_get_output_sequence();

	EXPECT_TRUE(fsm_out_sequence == expected_out_sequence);
}

TEST(FSMTestW, SequenceEquality11) {
	fsm_palindrom_srch fsm11;

	/* 0/1 0/1 1/0 2/1 2/0
	 * построенная строка по заданной последовательности. */
	std::string text_by_fsm_sequence11 = "LOL !";
	std::vector<fsm_output_symbol_t> fsm_out_sequence;
	fsm11.fsm_orchestrator_states(text_by_fsm_sequence11);

	std::vector<fsm_output_symbol_t> expected_out_sequence = {
	                                                           NODE_STATUS_COMPLETED,
	                                                           NODE_STATUS_COMPLETED,
	                                                           NODE_STATUS_FAILED,
	                                                           NODE_STATUS_COMPLETED,
	                                                           NODE_STATUS_FAILED
	                                                         };

	fsm_out_sequence = fsm11.fsm_get_output_sequence();

	EXPECT_TRUE(fsm_out_sequence == expected_out_sequence);
}

TEST(FSMTestW, SequenceEquality12) {
	fsm_palindrom_srch fsm12;

	/* 0/1 0/1 2/0 1/1 2/0
	 * построенная строка по заданной последовательности. */
	std::string text_by_fsm_sequence12 = "LL? ";
	std::vector<fsm_output_symbol_t> fsm_out_sequence;
	fsm12.fsm_orchestrator_states(text_by_fsm_sequence12);

	std::vector<fsm_output_symbol_t> expected_out_sequence = {
	                                                           NODE_STATUS_COMPLETED,
	                                                           NODE_STATUS_COMPLETED,
	                                                           NODE_STATUS_FAILED,
	                                                           NODE_STATUS_COMPLETED,
	                                                           NODE_STATUS_FAILED
	                                                         };

	fsm_out_sequence = fsm12.fsm_get_output_sequence();

	EXPECT_TRUE(fsm_out_sequence == expected_out_sequence);
}

TEST(FSMTestW, SequenceEquality13) {
	fsm_palindrom_srch fsm13;

	/* 0/1 0/1 2/0 2/1
	 * построенная строка по заданной последовательности. */
	std::string text_by_fsm_sequence13 = "LL_ ";
	std::vector<fsm_output_symbol_t> fsm_out_sequence;
	fsm13.fsm_orchestrator_states(text_by_fsm_sequence13);

	std::vector<fsm_output_symbol_t> expected_out_sequence = {
	                                                           NODE_STATUS_COMPLETED,
	                                                           NODE_STATUS_COMPLETED,
	                                                           NODE_STATUS_FAILED,
	                                                           NODE_STATUS_COMPLETED,
	                                                           NODE_STATUS_FAILED
	                                                         };

	fsm_out_sequence = fsm13.fsm_get_output_sequence();

	EXPECT_TRUE(fsm_out_sequence == expected_out_sequence);
}

TEST(FSMTestW, SequenceEquality14) {
	fsm_palindrom_srch fsm14;

	/* 0/1 2/0 2/0
	 * построенная строка по заданной последовательности. */
	std::string text_by_fsm_sequence14 = "R?!";
	std::vector<fsm_output_symbol_t> fsm_out_sequence;
	fsm14.fsm_orchestrator_states(text_by_fsm_sequence14);

	std::vector<fsm_output_symbol_t> expected_out_sequence = {
	                                                           NODE_STATUS_COMPLETED,
	                                                           NODE_STATUS_FAILED,
	                                                           NODE_STATUS_FAILED
	                                                         };

	fsm_out_sequence = fsm14.fsm_get_output_sequence();

	EXPECT_TRUE(fsm_out_sequence == expected_out_sequence);
}

TEST(FSMTestW, SequenceEquality15) {
	fsm_palindrom_srch fsm15;

	/* 0/1 1/0 2/0
	 * построенная строка по заданной последовательности. */
	std::string text_by_fsm_sequence15 = "Ra?";
	std::vector<fsm_output_symbol_t> fsm_out_sequence;
	fsm15.fsm_orchestrator_states(text_by_fsm_sequence15);

	std::vector<fsm_output_symbol_t> expected_out_sequence = {
	                                                           NODE_STATUS_COMPLETED,
	                                                           NODE_STATUS_FAILED,
	                                                           NODE_STATUS_FAILED
	                                                         };

	fsm_out_sequence = fsm15.fsm_get_output_sequence();

	EXPECT_TRUE(fsm_out_sequence == expected_out_sequence);
}

TEST(FSMTestW, SequenceEquality16) {
	fsm_palindrom_srch fsm16;

	/* 0/1 0/1 1/0 0/1 2/0
	 * построенная строка по заданной последовательности. */
	std::string text_by_fsm_sequence16 = "Kek' ";
	std::vector<fsm_output_symbol_t> fsm_out_sequence;
	fsm16.fsm_orchestrator_states(text_by_fsm_sequence16);

	std::vector<fsm_output_symbol_t> expected_out_sequence = {
	                                                           NODE_STATUS_COMPLETED,
	                                                           NODE_STATUS_COMPLETED,
	                                                           NODE_STATUS_FAILED,
	                                                           NODE_STATUS_COMPLETED,
	                                                           NODE_STATUS_FAILED
	                                                         };

	fsm_out_sequence = fsm16.fsm_get_output_sequence();

	EXPECT_TRUE(fsm_out_sequence == expected_out_sequence);
}

TEST(FSMTestW, SequenceEquality17) {
	fsm_palindrom_srch fsm17;

	/* 0/1 2/0 1/1 2/0
	 * построенная строка по заданной последовательности. */
	std::string text_by_fsm_sequence17 = "K 1 ";
	std::vector<fsm_output_symbol_t> fsm_out_sequence;
	fsm17.fsm_orchestrator_states(text_by_fsm_sequence17);

	std::vector<fsm_output_symbol_t> expected_out_sequence = {
	                                                           NODE_STATUS_COMPLETED,
	                                                           NODE_STATUS_FAILED,
	                                                           NODE_STATUS_COMPLETED,
	                                                           NODE_STATUS_FAILED
	                                                         };

	fsm_out_sequence = fsm17.fsm_get_output_sequence();

	EXPECT_TRUE(fsm_out_sequence == expected_out_sequence);
}

TEST(FSMTestW, SequenceEquality18) {
	fsm_palindrom_srch fsm18;

	/* 0/1 0/1 0/1 2/0
	 * построенная строка по заданной последовательности. */
	std::string text_by_fsm_sequence18 = "sss ";
	std::vector<fsm_output_symbol_t> fsm_out_sequence;
	fsm18.fsm_orchestrator_states(text_by_fsm_sequence18);

	std::vector<fsm_output_symbol_t> expected_out_sequence = {
	                                                           NODE_STATUS_COMPLETED,
	                                                           NODE_STATUS_COMPLETED,
	                                                           NODE_STATUS_COMPLETED,
	                                                           NODE_STATUS_FAILED
	                                                         };

	fsm_out_sequence = fsm18.fsm_get_output_sequence();

	EXPECT_TRUE(fsm_out_sequence == expected_out_sequence);
}