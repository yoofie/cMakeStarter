// Dear ImGui: standalone example application for SDL2 + OpenGL
// (SDL is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)
// (GL3W is a helper library to access OpenGL functions since there is no standard header to access modern OpenGL functions easily. Alternatives are GLEW, Glad, etc.)
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs
#include "async++.h"
#include "examples.h"
#include "fmt/bundled/format.h"
#include "result.h"

#include "ring.hpp"
#include "ring_span.hpp"
#include "sqlite3.h"
#include "version.h"
#include <filesystem>
#include <iostream>
#include "subprocess.hpp"
#ifdef TRACY_ENABLE
#include "tracy/Tracy.hpp"
#include "tracy/TracyC.h"
#endif

#ifdef DUCKDB_ENABLE
#include "duckdb.hpp"
#endif

int sqlite_cb_each_row(void *NotUsed, int argc, char **argv, char **azColName) {

	// Return successful
	return 0;
}

int main(int argc, char **) {
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif
	async::threadpool_scheduler custom_pool(4);

	using namespace std::chrono_literals;

	auto task1 = async::spawn(custom_pool, [] {
		std::this_thread::sleep_for(200ms);

		std::vector<uint32_t> v(3);
		nonstd::ring_span<uint32_t> ring(v.begin(), v.end());
		nonstd::ring<std::vector<uint32_t>> ring2(4);
		// nonstd::ring_span<uint32_t> rr(std::move(v));

		ring.push_back(1);
		ring.push_back(2);
		ring.push_back(3);
		ring.push_back(4);

		ring2.push_back(1);
		ring2.push_back(2);
		ring2.push_back(3);
		ring2.push_back(4);
		ring2.push_back(5);

		auto front = ring2.front();
		auto back = ring2.back();

		auto kk = ring2[3];

		auto &another = ring2;
		another.push_back(10);

		for (auto &i : ring) {
			std::cout << std::to_string(i) << "\n";
		}

		std::cout << "Task #1 executes asynchronously\n";
	});
	auto task2 = async::spawn(custom_pool, [] {
		auto appName  = fmt::format("{}.exe", APP_NAME);
		auto [explorer, length] = subprocess::check_output({"explorer", "/select,", appName});
		std::this_thread::sleep_for(800ms);
		std::cout << "Task #2 executes asynchronously\n";
	});
	auto task3 = async::spawn(custom_pool, [] {
		std::this_thread::sleep_for(200ms);
		std::cout << "Task #3 executes asynchronously\n";
	});

	auto task4 = async::when_all(task1, task2, task3);

	task4.then([]() {
		std::cout << "Size of char: " << sizeof(char) << "\n";
		std::cout << "Size of short: " << sizeof(short) << "\n";
		std::cout << "Size of INT: " << sizeof(int) << "\n";

		std::cout << "Size of float: " << sizeof(float) << "\n";
		std::cout << "Size of long: " << sizeof(long) << "\n";
		std::cout << "Size of double: " << sizeof(double) << "\n";
		std::cout << "Size of bool: " << sizeof(bool) << "\n";
		std::cout << "Size of long double: " << sizeof(long double) << "\n";

		std::cout << "\n---\nSize of uint8_t: " << sizeof(uint8_t) << "\n";
		auto x = fmt::format("Just a string with a arbitrary number {}", 42);
		printf("%s\n", x.c_str());
		std::cout << "Finished running!\n";
	});
#ifdef ENABLE_SQLITE
	auto sqlite = async::spawn(custom_pool, [] {
		std::string fileName = "ddd.db";
		std::string retval = "DB Export OK";

		std::string sql;
		printf("SQLITE = %s | %s\n", sqlite3_libversion(), APP_NAME);
		sqlite3 *db;

		// Save any error messages
		char *zErrMsg = 0;

		// Save the result of opening the file
		int opResult = 0;

		// Save the result of opening the file
		opResult = sqlite3_open(fileName.c_str(), &db);

		if (opResult) {
			retval = sqlite3_errmsg(db);
			// Close the connection
			sqlite3_close(db);
			// return Err(retval);
		}

		// Save SQL to create a table
		sql = "CREATE TABLE export_json ("
			  "ID INT PRIMARY KEY     NOT NULL,"
			  "KV_NAME TEXT     NOT NULL,"
			  "KV_VALUE TEXT    NOT NULL);";

		// Run the SQL (convert the string to a C-String with c_str() )
		opResult = sqlite3_exec(db, sql.c_str(), sqlite_cb_each_row, 0, &zErrMsg);

		sql = fmt::format("INSERT INTO export_json (ID, KV_NAME, KV_VALUE) VALUES ({}, '{}', '{}')", 1, "full_json", "dummy_values");
		opResult = sqlite3_exec(db, sql.c_str(), sqlite_cb_each_row, 0, &zErrMsg);
		// Close the SQL connection
		sqlite3_close(db);
	});
#endif
#ifdef DUCKDB_ENABLE
	auto duckdb = async::spawn(custom_pool, []() {
		duckdb::DuckDB db(nullptr);
		duckdb::Connection con(db);
		auto result = con.Query("SELECT 42");
		result->Print();
	});
#endif

	return 0;
}
