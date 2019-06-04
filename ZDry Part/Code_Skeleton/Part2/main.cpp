#include "Game.hpp"
#include <string.h>
#define TILE_IDS_FILE_NAME "tiles_ids.csv"
static inline game_params parse_input_args(int argc, char **argv);
static inline void usage(const char* mes);
static void calc_and_append_statistics(uint n_threads, const vector<double>& gen_hist, const vector<tile_record>& tile_hist,uint init_n_threads);

/*--------------------------------------------------------------------------------
										Main
--------------------------------------------------------------------------------*/
int main(int argc, char **argv) {

	game_params params = parse_input_args(argc, argv);
	Game g(params);
	g.run();
	calc_and_append_statistics(g.thread_num(), g.gen_hist(), g.tile_hist(),params.n_thread);
	return 0;
}
/*--------------------------------------------------------------------------------
							 Auxiliary Implementation
--------------------------------------------------------------------------------*/
static inline game_params parse_input_args(int argc, char **argv) {

	if (argc != 6) // ./gameoflife filename.txt 100 20 Y Y
		usage("Wrong number of arguments - expected 5");

	game_params g;
	g.filename = argv[1];
	g.n_gen = strtoul(argv[2], NULL, 10);
	g.n_thread = strtoul(argv[3], NULL, 10);

	string inter = string(argv[4]);
	string print = string(argv[5]);
	g.interactive_on = (inter == "y" || inter == "Y") ? true : false;
	g.print_on = (print == "y" || print == "Y") ? true : false;

	if (g.n_gen <= 0 || g.n_thread <= 0)
		usage("Invalid number of generations/number of threads (Required: integer >0)");
	return g;
}

static inline void usage(const char* mes) {
	cerr << "Usage Error : " << mes
		<< "\nUse format: ./GameOfLife <matrixfile.txt> <number_of_generations> <number_of_threads> <Y/N> <Y/N>\n"
		<< "Last two are flags for (1) interactive mode , (2) output to screen\n";
	exit(1);
}


static void calc_and_append_statistics(uint n_threads, const vector<double>& gen_hist, const vector<tile_record>& tile_hist,uint init_n_threads) {

	double total_time = (double)accumulate(gen_hist.begin(), gen_hist.end(), 0.0);
	double avg_gen_time = total_time / gen_hist.size();

	double avg_tile_time = 0;
	for(uint i=0 ; i<tile_hist.size() ; ++i){
		//cout <<"Tile time = "<< tile_hist[i].tile_compute_time << endl;
		avg_tile_time += tile_hist[i].tile_compute_time;
	}
	avg_tile_time /= tile_hist.size();
	double gen_rate = gen_hist.size() / total_time;
	double tile_rate = tile_hist.size() / total_time;

	ifstream ifile(DEF_RESULTS_FILE_NAME);
	bool file_exists = ifile.good();
	ifile.close();

	std::ofstream results_file(DEF_RESULTS_FILE_NAME, std::ofstream::app | std::ofstream::out);
	if (!file_exists)
	{
		results_file << "EffectiveThreadNum,GenNum,Gen_Rate[1/us],Avg_Gen_Time[us],Tile_Rate[1/us],Avg_Tile_Time[us],Total_Time[us]" << endl;
		// cout << "Successfully created results file: " << DEF_RESULTS_FILE_NAME << endl;
	}

	results_file.close();


	results_file << n_threads << "," << gen_hist.size() << "," << gen_rate << "," << avg_gen_time << "," << tile_rate
		<< "," << avg_tile_time << "," << total_time << endl;

		ifstream ifile2(TILE_IDS_FILE_NAME+std::to_string(init_n_threads));
		bool file_exists2 = ifile2.good();
		ifile2.close();

		std::ofstream results_file2(TILE_IDS_FILE_NAME+std::to_string(init_n_threads),std::ofstream::out);
		if (!file_exists2)
		{
			results_file2 << "Index,ThreadID" << endl;
			// cout << "Successfully created results file: " << DEF_RESULTS_FILE_NAME << endl;
		}
		for (uint j = 0; j < tile_hist.size(); j++)
		{
			results_file2 << j << "," << tile_hist[j].thread_id << endl;
		}


		results_file2.close();
}
