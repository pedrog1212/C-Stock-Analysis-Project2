#pragma once
#include "pch.h"
#include "Form_mainUI.h"
//include the technical analizer class
#include "TechnicalAnalizer.h"

namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Windows::Forms::DataVisualization::Charting;
	using namespace System::Collections::Generic;

	/// <summary>
	/// Summary for Form_mainUI
	/// </summary>
	public ref class Form_mainUI : public System::Windows::Forms::Form
	{

	//property to store the list of all candlestick objects.
	property List<Candlestick^>^ candlesticks;

	//property to store the filtered list of candlestick objects.
	property List<Candlestick^>^ filteredCandlesticks;

	//property to store the dictionary
	property Dictionary<int, List<PeaksAndValleys^>^>^ peakAndValleyDict;

	//property to store the peaks and valleys 
	property List<PeaksAndValleys^>^ listPeaksAndValleys;

	//property to hold the margin from the horizontal scroll bar
	property int margin;

	//property to hold the file path as a string
	property System::String^ filePath;

	public:
		Form_mainUI(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

		/// <summary>
		/// Initializes a new instance of the Form_mainUI class using the given file path, 
		/// date range, and candlestick data. It sets up the UI, filters data within the date range, 
		/// fetches peaks and valleys for the selected margin, and populates the chart or 
		/// shows a warning if no data exists for the specified range.
		/// </summary>
		/// <param name="path">The path of the loaded stock data file.</param>
		/// <param name="start">The start date for filtering candlestick data.</param>
		/// <param name="end">The end date for filtering candlestick data.</param>
		/// <param name="candlestickData">The list of all candlestick data read from the file.</param>
		Form_mainUI(String^ path, DateTime start, DateTime end, List<Candlestick^>^ candlestickData)
		{
			//initialize UI components like chart, scrollbars, combo boxes, etc.
			InitializeComponent();

			//store the full candlestick dataset passed to the constructor.
			candlesticks = candlestickData;

			//store the file path string.
			filePath = path;

			//get the selected margin value from the scrollbar.
			margin = hScrollBar_margin->Value;

			//filter candlestick data between the specified start and end dates.
			filteredCandlesticks = TechnicalAnalizer::filterDataByDate(candlesticks, start, end);

			//generate a dictionary of peaks and valleys for different margins.
			peakAndValleyDict = TechnicalAnalizer::assignPeaksAndValleysDict(filteredCandlesticks);

			//set the UI's start date picker to the selected start date.
			dateTimePicker_start->Value = start;

			//set the UI's end date picker to the selected end date.
			dateTimePicker_end->Value = end;

			//only proceed if the peak and valley dictionary contains data for the current margin.
			if (peakAndValleyDict->ContainsKey(margin))
			{
				//retrieve the list of peak and valley points for the selected margin.
				listPeaksAndValleys = peakAndValleyDict[margin];
			}
			else
			{
				//show a warning message if no data exists for this date range and file.
				System::Windows::Forms::DialogResult result = System::Windows::Forms::MessageBox::Show(
					"The selected file '" + path + "' has no values between these dates. Change the file or the dates",
					"Warning",
					System::Windows::Forms::MessageBoxButtons::OK,
					System::Windows::Forms::MessageBoxIcon::Warning
				);

				//hide the candlestick chart to indicate there's no data to display.
				chart_candlestick->Visible = false;

				//initialize an empty list to avoid null reference issues later on.
				listPeaksAndValleys = gcnew List<PeaksAndValleys^>();
			}

			//check again if filtered data is completely empty.
			if (filteredCandlesticks->Count == 0)
			{
				//display the same warning message as above.
				System::Windows::Forms::DialogResult result = System::Windows::Forms::MessageBox::Show(
					"The selected file '" + path + "' has no values between these dates. Change the file or the dates",
					"Warning",
					System::Windows::Forms::MessageBoxButtons::OK,
					System::Windows::Forms::MessageBoxIcon::Warning
				);

				//hide the candlestick chart due to lack of data.
				chart_candlestick->Visible = false;
			}
			else
			{
				//display the chart and candlestick data visually.
				displayData();

				//populate the wave start and end combo boxes with valid wave options.
				populateWaveComboBoxes();
			}
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form_mainUI()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:
	private: System::Windows::Forms::Button^ button_load;
	private: System::Windows::Forms::DateTimePicker^ dateTimePicker_end;
	private: System::Windows::Forms::Label^ label_end;
	private: System::Windows::Forms::DateTimePicker^ dateTimePicker_start;
	private: System::Windows::Forms::Label^ label_start;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog_filePicker;

	private: System::Windows::Forms::Button^ button_update;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart_candlestick;
	private: System::Windows::Forms::HScrollBar^ hScrollBar_margin;
	private: System::Windows::Forms::Label^ label_margin;
	private: System::Windows::Forms::ComboBox^ comboBox_waveUp;
	private: System::Windows::Forms::ComboBox^ comboBox_waveDown;
	private: System::Windows::Forms::Label^ label_waveUp;
	private: System::Windows::Forms::Label^ label_waveDown;




	private: System::Windows::Forms::Button^ button_clearPeaksAndValleys;
	private: System::Windows::Forms::Button^ button_clearWaves;

	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code

		void InitializeComponent(void)
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^ series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->button_load = (gcnew System::Windows::Forms::Button());
			this->dateTimePicker_end = (gcnew System::Windows::Forms::DateTimePicker());
			this->label_end = (gcnew System::Windows::Forms::Label());
			this->dateTimePicker_start = (gcnew System::Windows::Forms::DateTimePicker());
			this->label_start = (gcnew System::Windows::Forms::Label());
			this->openFileDialog_filePicker = (gcnew System::Windows::Forms::OpenFileDialog());
			this->button_update = (gcnew System::Windows::Forms::Button());
			this->chart_candlestick = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->hScrollBar_margin = (gcnew System::Windows::Forms::HScrollBar());
			this->label_margin = (gcnew System::Windows::Forms::Label());
			this->comboBox_waveUp = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox_waveDown = (gcnew System::Windows::Forms::ComboBox());
			this->label_waveUp = (gcnew System::Windows::Forms::Label());
			this->label_waveDown = (gcnew System::Windows::Forms::Label());
			this->button_clearPeaksAndValleys = (gcnew System::Windows::Forms::Button());
			this->button_clearWaves = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart_candlestick))->BeginInit();
			this->SuspendLayout();
			// 
			// button_load
			// 
			this->button_load->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->button_load->BackColor = System::Drawing::Color::Green;
			this->button_load->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button_load->Location = System::Drawing::Point(556, 419);
			this->button_load->Name = L"button_load";
			this->button_load->Size = System::Drawing::Size(123, 49);
			this->button_load->TabIndex = 0;
			this->button_load->Text = L"Load Stock";
			this->button_load->UseVisualStyleBackColor = false;
			this->button_load->Click += gcnew System::EventHandler(this, &Form_mainUI::button_load_Click);
			// 
			// dateTimePicker_end
			// 
			this->dateTimePicker_end->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->dateTimePicker_end->Location = System::Drawing::Point(12, 496);
			this->dateTimePicker_end->Name = L"dateTimePicker_end";
			this->dateTimePicker_end->Size = System::Drawing::Size(204, 20);
			this->dateTimePicker_end->TabIndex = 12;
			this->dateTimePicker_end->Value = System::DateTime(2021, 2, 28, 0, 0, 0, 0);
			this->dateTimePicker_end->ValueChanged += gcnew System::EventHandler(this, &Form_mainUI::dateTimePicker_start_ValueChanged);
			// 
			// label_end
			// 
			this->label_end->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->label_end->AutoSize = true;
			this->label_end->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_end->Location = System::Drawing::Point(12, 480);
			this->label_end->Name = L"label_end";
			this->label_end->Size = System::Drawing::Size(31, 16);
			this->label_end->TabIndex = 11;
			this->label_end->Text = L"End";
			// 
			// dateTimePicker_start
			// 
			this->dateTimePicker_start->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->dateTimePicker_start->Location = System::Drawing::Point(12, 441);
			this->dateTimePicker_start->Name = L"dateTimePicker_start";
			this->dateTimePicker_start->Size = System::Drawing::Size(204, 20);
			this->dateTimePicker_start->TabIndex = 10;
			this->dateTimePicker_start->Value = System::DateTime(2021, 2, 10, 0, 0, 0, 0);
			this->dateTimePicker_start->ValueChanged += gcnew System::EventHandler(this, &Form_mainUI::dateTimePicker_start_ValueChanged);
			// 
			// label_start
			// 
			this->label_start->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->label_start->AutoSize = true;
			this->label_start->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_start->Location = System::Drawing::Point(9, 425);
			this->label_start->Name = L"label_start";
			this->label_start->Size = System::Drawing::Size(34, 16);
			this->label_start->TabIndex = 9;
			this->label_start->Text = L"Start";
			// 
			// openFileDialog_filePicker
			// 
			this->openFileDialog_filePicker->DefaultExt = L"csv";
			this->openFileDialog_filePicker->FileName = L"ABBV-Day";
			this->openFileDialog_filePicker->Filter = L"All|*.csv|Monthly|*-Month.csv|Weekly|*-Week.csv|Daily|*-Day.csv";
			this->openFileDialog_filePicker->InitialDirectory = L"..\\Stock Data";
			this->openFileDialog_filePicker->Multiselect = true;
			this->openFileDialog_filePicker->ReadOnlyChecked = true;
			this->openFileDialog_filePicker->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Form_mainUI::openFileDialog_filePicker_FileOk);
			// 
			// button_update
			// 
			this->button_update->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->button_update->BackColor = System::Drawing::Color::Goldenrod;
			this->button_update->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button_update->Location = System::Drawing::Point(695, 419);
			this->button_update->Name = L"button_update";
			this->button_update->Size = System::Drawing::Size(123, 49);
			this->button_update->TabIndex = 15;
			this->button_update->Text = L"Update";
			this->button_update->UseVisualStyleBackColor = false;
			this->button_update->Visible = false;
			this->button_update->Click += gcnew System::EventHandler(this, &Form_mainUI::button_update_Click);
			// 
			// chart_candlestick
			// 
			this->chart_candlestick->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			chartArea1->Name = L"ChartArea_candlestick";
			chartArea2->AlignWithChartArea = L"ChartArea_candlestick";
			chartArea2->Name = L"ChartArea_volume";
			this->chart_candlestick->ChartAreas->Add(chartArea1);
			this->chart_candlestick->ChartAreas->Add(chartArea2);
			legend1->Enabled = false;
			legend1->Name = L"Legend1";
			this->chart_candlestick->Legends->Add(legend1);
			this->chart_candlestick->Location = System::Drawing::Point(0, 0);
			this->chart_candlestick->Name = L"chart_candlestick";
			series1->BorderColor = System::Drawing::Color::Black;
			series1->BorderWidth = 3;
			series1->ChartArea = L"ChartArea_candlestick";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Candlestick;
			series1->CustomProperties = L"PriceDownColor=Red, PriceUpColor=Green";
			series1->IsXValueIndexed = true;
			series1->Legend = L"Legend1";
			series1->Name = L"Series_candlestick";
			series1->XValueMember = L"Date";
			series1->XValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::Date;
			series1->YValueMembers = L"High, Low, Open, Close";
			series1->YValuesPerPoint = 4;
			series2->ChartArea = L"ChartArea_volume";
			series2->IsXValueIndexed = true;
			series2->Legend = L"Legend1";
			series2->Name = L"Series_volume";
			series2->XValueMember = L"Date";
			series2->XValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::Date;
			series2->YValueMembers = L"Volume";
			this->chart_candlestick->Series->Add(series1);
			this->chart_candlestick->Series->Add(series2);
			this->chart_candlestick->Size = System::Drawing::Size(889, 408);
			this->chart_candlestick->TabIndex = 14;
			this->chart_candlestick->Text = L"chart1";
			this->chart_candlestick->TextAntiAliasingQuality = System::Windows::Forms::DataVisualization::Charting::TextAntiAliasingQuality::SystemDefault;
			// 
			// hScrollBar_margin
			// 
			this->hScrollBar_margin->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->hScrollBar_margin->Cursor = System::Windows::Forms::Cursors::NoMoveHoriz;
			this->hScrollBar_margin->LargeChange = 1;
			this->hScrollBar_margin->Location = System::Drawing::Point(241, 498);
			this->hScrollBar_margin->Maximum = 8;
			this->hScrollBar_margin->Minimum = 1;
			this->hScrollBar_margin->Name = L"hScrollBar_margin";
			this->hScrollBar_margin->Size = System::Drawing::Size(248, 25);
			this->hScrollBar_margin->TabIndex = 16;
			this->hScrollBar_margin->Value = 1;
			this->hScrollBar_margin->Visible = false;
			this->hScrollBar_margin->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &Form_mainUI::hScrollBar_margin_Scroll);
			// 
			// label_margin
			// 
			this->label_margin->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->label_margin->AutoSize = true;
			this->label_margin->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_margin->Location = System::Drawing::Point(238, 485);
			this->label_margin->Name = L"label_margin";
			this->label_margin->Size = System::Drawing::Size(64, 16);
			this->label_margin->TabIndex = 17;
			this->label_margin->Text = L"Margin : 1";
			this->label_margin->Visible = false;
			// 
			// comboBox_waveUp
			// 
			this->comboBox_waveUp->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->comboBox_waveUp->FormattingEnabled = true;
			this->comboBox_waveUp->Location = System::Drawing::Point(241, 440);
			this->comboBox_waveUp->Name = L"comboBox_waveUp";
			this->comboBox_waveUp->Size = System::Drawing::Size(144, 21);
			this->comboBox_waveUp->TabIndex = 18;
			this->comboBox_waveUp->SelectedIndexChanged += gcnew System::EventHandler(this, &Form_mainUI::comboBox_waveUp_SelectedIndexChanged);
			// 
			// comboBox_waveDown
			// 
			this->comboBox_waveDown->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->comboBox_waveDown->FormattingEnabled = true;
			this->comboBox_waveDown->Location = System::Drawing::Point(391, 440);
			this->comboBox_waveDown->Name = L"comboBox_waveDown";
			this->comboBox_waveDown->Size = System::Drawing::Size(144, 21);
			this->comboBox_waveDown->TabIndex = 19;
			this->comboBox_waveDown->SelectedIndexChanged += gcnew System::EventHandler(this, &Form_mainUI::comboBox_waveDown_SelectedIndexChanged);
			// 
			// label_waveUp
			// 
			this->label_waveUp->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->label_waveUp->AutoSize = true;
			this->label_waveUp->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_waveUp->Location = System::Drawing::Point(238, 423);
			this->label_waveUp->Name = L"label_waveUp";
			this->label_waveUp->Size = System::Drawing::Size(71, 16);
			this->label_waveUp->TabIndex = 20;
			this->label_waveUp->Text = L"Up Waves";
			// 
			// label_waveDown
			// 
			this->label_waveDown->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->label_waveDown->AutoSize = true;
			this->label_waveDown->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_waveDown->Location = System::Drawing::Point(388, 423);
			this->label_waveDown->Name = L"label_waveDown";
			this->label_waveDown->Size = System::Drawing::Size(87, 16);
			this->label_waveDown->TabIndex = 21;
			this->label_waveDown->Text = L"Down Waves";
			// 
			// button_clearPeaksAndValleys
			// 
			this->button_clearPeaksAndValleys->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->button_clearPeaksAndValleys->BackColor = System::Drawing::Color::YellowGreen;
			this->button_clearPeaksAndValleys->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->button_clearPeaksAndValleys->Location = System::Drawing::Point(556, 485);
			this->button_clearPeaksAndValleys->Name = L"button_clearPeaksAndValleys";
			this->button_clearPeaksAndValleys->Size = System::Drawing::Size(123, 49);
			this->button_clearPeaksAndValleys->TabIndex = 22;
			this->button_clearPeaksAndValleys->Text = L"Clear Peaks and Valleys";
			this->button_clearPeaksAndValleys->UseVisualStyleBackColor = false;
			this->button_clearPeaksAndValleys->Click += gcnew System::EventHandler(this, &Form_mainUI::button_clearPeaksAndValleys_Click);
			// 
			// button_clearWaves
			// 
			this->button_clearWaves->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->button_clearWaves->BackColor = System::Drawing::Color::YellowGreen;
			this->button_clearWaves->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button_clearWaves->Location = System::Drawing::Point(695, 485);
			this->button_clearWaves->Name = L"button_clearWaves";
			this->button_clearWaves->Size = System::Drawing::Size(123, 49);
			this->button_clearWaves->TabIndex = 23;
			this->button_clearWaves->Text = L"Clear Waves";
			this->button_clearWaves->UseVisualStyleBackColor = false;
			this->button_clearWaves->Click += gcnew System::EventHandler(this, &Form_mainUI::button_clearWaves_Click);
			// 
			// Form_mainUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(889, 567);
			this->Controls->Add(this->button_clearWaves);
			this->Controls->Add(this->button_clearPeaksAndValleys);
			this->Controls->Add(this->label_waveDown);
			this->Controls->Add(this->label_waveUp);
			this->Controls->Add(this->comboBox_waveDown);
			this->Controls->Add(this->comboBox_waveUp);
			this->Controls->Add(this->label_margin);
			this->Controls->Add(this->hScrollBar_margin);
			this->Controls->Add(this->button_load);
			this->Controls->Add(this->dateTimePicker_end);
			this->Controls->Add(this->label_end);
			this->Controls->Add(this->dateTimePicker_start);
			this->Controls->Add(this->label_start);
			this->Controls->Add(this->button_update);
			this->Controls->Add(this->chart_candlestick);
			this->MinimumSize = System::Drawing::Size(905, 606);
			this->Name = L"Form_mainUI";
			this->Text = L"Main UI";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart_candlestick))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	/// <summary>
	/// Displays the file picker dialog to allow user to select stock CSV files.
	/// </summary>
	private: System::Void button_load_Click(System::Object^ sender, System::EventArgs^ e)
	{
		//show the file picker dialog for the user to select CSV files
		openFileDialog_filePicker->ShowDialog();
	}
	
	/// <summary>
    /// Processes the selected CSV file(s), loads the data, filters it by date range, 
    /// assigns peaks and valleys, and displays the data in the chart.
    /// Opens additional forms for each selected file after the first.
    /// </summary>
	private: System::Void openFileDialog_filePicker_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e)
	{
		//clear the waves
		clearWaveAnnotations();

		//make the margin label visible
		label_margin->Visible = true;

		//make the horizontal scroll bar visible
		hScrollBar_margin->Visible = true;

		//check if at least one file is selected
		if (openFileDialog_filePicker->FileNames->Length > 0)
		{
			//load the first selected file into the current form
			filePath = openFileDialog_filePicker->FileNames[0];
			candlesticks = TechnicalAnalizer::ReadFromCSV(filePath);
			filteredCandlesticks = TechnicalAnalizer::filterDataByDate(candlesticks, dateTimePicker_start->Value, dateTimePicker_end->Value);
			margin = hScrollBar_margin->Value;
			peakAndValleyDict = TechnicalAnalizer::assignPeaksAndValleysDict(filteredCandlesticks);

			//only assign if dictionary has this margin
			if (peakAndValleyDict->ContainsKey(margin))
			{
				//list of PeakAndValley objects which hold all the candlesticks which are peaks or valleys, retrieved from dictionary or computed
				listPeaksAndValleys = peakAndValleyDict[margin];
			}
			else
			{
				//make the list empty to avoid null
				listPeaksAndValleys = gcnew List<PeaksAndValleys^>();
			}

			//update UI elements accordingly
			this->Text = filePath;

			//display a warning if there is not date between the selected dates for the selected file
			if (filteredCandlesticks->Count == 0)
			{
				System::Windows::Forms::MessageBox::Show(
					"The selected file '" + filePath + "' has no values between these dates. Change the file or the dates.",
					"Warning",
					System::Windows::Forms::MessageBoxButtons::OK,
					System::Windows::Forms::MessageBoxIcon::Warning
				);
				chart_candlestick->Visible = false;
				button_load->Visible = true;
				button_update->Visible = false;
			}
			else
			{
				//populate the combo boxes
				populateWaveComboBoxes();

				//make the update button visible
				button_update->Visible = true;

				//make the chart visible
				chart_candlestick->Visible = true;

				//display the data
				displayData();
			}

			//if there are additional selected files, open new forms for them
			for (int i = 1; i < openFileDialog_filePicker->FileNames->Length; i++)
			{
				//get the path of the next selected file
				String^ additionalFilePath = openFileDialog_filePicker->FileNames[i];

				//read candlestick data from that file
				List<Candlestick^>^ additionalCandlesticks = TechnicalAnalizer::ReadFromCSV(additionalFilePath);

				//create a new instance of the main UI form using the selected file's data and current date range
				Form_mainUI^ newForm = gcnew Form_mainUI(additionalFilePath, dateTimePicker_start->Value, dateTimePicker_end->Value, additionalCandlesticks);

				//set the window title of the new form to show the file path
				newForm->Text = additionalFilePath;

				//hide the load button in the new form since it's already loaded
				newForm->button_load->Visible = false;

				//show the update button in the new form so the user can reprocess the data
				newForm->button_update->Visible = true;

				//adjust the size of the update button to make it more prominent
				newForm->button_update->Size = System::Drawing::Size(262, 49);

				//adjust the location of the update button to make it more prominent
				newForm->button_update->Location = System::Drawing::Point(556, 419);

				//display the new form to the user
				newForm->Show();

				//make the margin label visible
				newForm->label_margin->Visible = true;

				//make the horizontal scroll bar visible
				newForm->hScrollBar_margin->Visible = true;
			}
		}
	}

	/// <summary>
    /// Updates the displayed candlestick data and wave information using the current date range and margin.
    /// Shows a warning if no data exists for the selected range.
    /// </summary>
	private: System::Void button_update_Click(System::Object^ sender, System::EventArgs^ e)
	{
		//clear waves
		clearWaveAnnotations();

		//update the margin value from the scrollbar
		margin = hScrollBar_margin->Value;

		//filter candlesticks by the currently selected start and end date
		filteredCandlesticks = TechnicalAnalizer::filterDataByDate(candlesticks, dateTimePicker_start->Value, dateTimePicker_end->Value);

		//regenerate the peak and valley dictionary from the new filtered data
		peakAndValleyDict = TechnicalAnalizer::assignPeaksAndValleysDict(filteredCandlesticks);

		//check again if there’s absolutely no filtered data
		if (filteredCandlesticks->Count == 0)
		{
			//warn user that no data is available
			System::Windows::Forms::MessageBox::Show(
				"The selected file '" + filePath + "' has no values between these dates. Change the file or the dates",
				"Warning",
				System::Windows::Forms::MessageBoxButtons::OK,
				System::Windows::Forms::MessageBoxIcon::Warning
			);
		}
		else
		{
			//check if the dictionary contains data for this margin
			if (peakAndValleyDict->ContainsKey(margin))
			{
				//update the peak and valley list
				listPeaksAndValleys = peakAndValleyDict[margin];
			}
			else
			{
				//set an empty peak/valley list to avoid null references
				listPeaksAndValleys = gcnew List<PeaksAndValleys^>();
			}

			//repopulate the combo boxes for wave selection
			populateWaveComboBoxes();

			//display the updated data on chart
			displayData();
		}
	}

	/// <summary>
	///Displays the filtered candlestick data in the DataGridView and chart.
	/// </summary>
	private: System::Void displayData()
	{
		//filter data based on the selected date range.
		filteredCandlesticks = TechnicalAnalizer::filterDataByDate(candlesticks, dateTimePicker_start->Value, dateTimePicker_end->Value);

		//if there is no candlesticks in the filtered list return as there is no data to display
		if (filteredCandlesticks->Count == 0)
			return;

		//bind the filtered list to the DataGridView.
		BindingList<Candlestick^>^ bindingList = gcnew BindingList<Candlestick^>(filteredCandlesticks);

		//normalize the chart display.
		normalizeDisplay();

		//bind the filtered data to the candlestick chart.
		chart_candlestick->DataSource = bindingList;
		chart_candlestick->DataBind();

		//call the function to put all the annotations for each peak and valley
		annotatePeakAndValleys();
	}

	/// <summary>
	///Adjusts the Y-axis range of the candlestick chart dynamically based on the filtered data.
	/// </summary>
	private: System::Void normalizeDisplay()
	{
		//find the maximum high value in the filtered data.
		double maxValue = filteredCandlesticks[0]->High;

		//iterate through each candlestick in the filtered list to find the minimum low value.
		for each (Candlestick ^ candlestick in filteredCandlesticks)
		{
			//check if the current candlestick's high value is greater than the current max value.
			if (candlestick->High > maxValue)
			{
				//update the max value if the current candlestick's high is greater.
				maxValue = candlestick->High;
			}
		}

		//find the minimum low value in the filtered data.
		double minValue = filteredCandlesticks[0]->Low;

		//iterate through each candlestick in the filtered list to find the minimum low value.
		for each (Candlestick ^ candlestick in filteredCandlesticks)
		{
			//check if the current candlestick's low value is less than the current min value.
			if (candlestick->Low < minValue)
			{
				//update the min value if the current candlestick's low is smaller.
				minValue = candlestick->Low;
			}
		}

		//add padding so the candlestick is not touching the edge of the chart.
		double padding = (maxValue - minValue) * 0.2;
		minValue -= padding;
		maxValue += padding;

		//round max and min values to 2 decimal places.
		minValue = Math::Round(minValue, 2);
		maxValue = Math::Round(maxValue, 2);

		//set Y-Axis range dynamically.
		chart_candlestick->ChartAreas["ChartArea_candlestick"]->AxisY->Minimum = minValue;
		chart_candlestick->ChartAreas["ChartArea_candlestick"]->AxisY->Maximum = maxValue;
	}

	/// <summary>
	/// Adds red "v" for peaks and green "^" for valleys on the candlestick chart.
	/// </summary>
	private: System::Void annotatePeakAndValleys()
	{
		//clear all existing annotations related to peaks and valleys
		clearPeakValleyAnnotations();

		//get the candlestick chart area
		ChartArea^ chart = chart_candlestick->ChartAreas["ChartArea_candlestick"];

		//calculate an offset based on the Y-axis range
		double yMin = chart->AxisY->Minimum;
		double yMax = chart->AxisY->Maximum;
		double offset = (yMax - yMin) * 0.08; // 8% of range

		//loop through each peak or valley in the list
		for each(PeaksAndValleys ^ pv in listPeaksAndValleys)
		{
			//find the index in the filtered data
			int index = -1;
			for (int i = 0; i < filteredCandlesticks->Count; i++)
			{
				if (filteredCandlesticks[i]->Date == pv->Date)
				{
					index = i;
					break;
				}
			}

			//if the list is empty continue
			if (index == -1) continue;

			//get the data point from the chart
			DataPoint^ dataPoint = chart_candlestick->Series["Series_candlestick"]->Points[index];

			//choose symbol and color
			String^ symbol = pv->isPeak ? "v" : "^";
			Color color = pv->isPeak ? Color::Red : Color::Green;

			//set anchor Y
			double anchorY = pv->isPeak ? (double)pv->High + offset : (double)pv->Low - offset;

			if (pv->isPeak && pv->isValley)
			{
				//add ▼ for peak
				TextAnnotation^ peakAnnotation = gcnew TextAnnotation();
				peakAnnotation->Text = "v";
				peakAnnotation->ForeColor = Color::Red;
				peakAnnotation->Font = gcnew Drawing::Font("Arial", 14, FontStyle::Bold);
				peakAnnotation->Name = "peak_" + index.ToString();
				peakAnnotation->Alignment = ContentAlignment::MiddleCenter;
				peakAnnotation->AnchorAlignment = ContentAlignment::MiddleCenter;
				peakAnnotation->ClipToChartArea = chart->Name;
				peakAnnotation->AnchorX = index + 1;
				peakAnnotation->AnchorY = (double)pv->High + offset;
				peakAnnotation->AnchorDataPoint = dataPoint;

				//add ▲ for valley
				TextAnnotation^ valleyAnnotation = gcnew TextAnnotation();
				valleyAnnotation->Text = "^";
				valleyAnnotation->ForeColor = Color::Green;
				valleyAnnotation->Font = gcnew Drawing::Font("Arial", 14, FontStyle::Bold);
				valleyAnnotation->Name = "valley_" + index.ToString();
				valleyAnnotation->Alignment = ContentAlignment::MiddleCenter;
				valleyAnnotation->AnchorAlignment = ContentAlignment::MiddleCenter;
				valleyAnnotation->ClipToChartArea = chart->Name;
				valleyAnnotation->AnchorX = index + 1;
				valleyAnnotation->AnchorY = (double)pv->Low - offset;
				valleyAnnotation->AnchorDataPoint = dataPoint;

				//add both annotations to chart
				chart_candlestick->Annotations->Add(peakAnnotation);
				chart_candlestick->Annotations->Add(valleyAnnotation);
			}
			else
			{
				//single annotation (either peak or valley)
				TextAnnotation^ annotation = gcnew TextAnnotation();
				annotation->Text = symbol;
				annotation->ForeColor = color;
				annotation->Font = gcnew Drawing::Font("Arial", 14, FontStyle::Bold);
				annotation->Name = pv->isPeak ? "peak_" + index.ToString() : "valley_" + index.ToString();
				annotation->Alignment = ContentAlignment::MiddleCenter;
				annotation->AnchorAlignment = ContentAlignment::MiddleCenter;
				annotation->ClipToChartArea = chart->Name;
				annotation->AnchorX = index + 1;
				annotation->AnchorY = anchorY;
				annotation->AnchorDataPoint = dataPoint;

				//add annotation to chart
				chart_candlestick->Annotations->Add(annotation);
			}
		}

		//force the chart to redraw
		chart_candlestick->Invalidate();
		chart_candlestick->Update();
	}

	/// <summary>
	/// Handles margin scroll event to update the peak and valley list and re-annotate chart accordingly.
	/// </summary>
	private: System::Void hScrollBar_margin_Scroll(System::Object^ sender, System::Windows::Forms::ScrollEventArgs^ e)
	{
		//clear waves
		clearWaveAnnotations();

		//update the margin value from the scrollbar
		margin = hScrollBar_margin->Value;

		//update label text to show current margin
		label_margin->Text = margin.ToString();

		//check if peak and valley data exists for this margin
		if (peakAndValleyDict->ContainsKey(margin))
		{
			//load peaks and valleys for the selected margin
			listPeaksAndValleys = peakAndValleyDict[margin];

			//refresh the annotations on the chart
			annotatePeakAndValleys();

			//populate the combo boxes with wave options
			populateWaveComboBoxes();
		}
		else
		{
			//clear all peak/valley annotations if none for this margin
			button_clearPeaksAndValleys_Click(nullptr, nullptr);

			//clear combo boxes to reflect lack of data
			comboBox_waveUp->Items->Clear();
			comboBox_waveDown->Items->Clear();
		}

		//redraw the chart to reflect updated state
		chart_candlestick->Invalidate();
		chart_candlestick->Update();
	}

	/// <summary>
	/// Populates the wave combo boxes with valid up and down waves.
	/// </summary>
	private: System::Void populateWaveComboBoxes()
	{
		//get the up and down wave date ranges from TechnicalAnalizer
		System::Tuple<List<String^>^, List<String^>^>^ waveResults = TechnicalAnalizer::getUpAndDownWaveDates(listPeaksAndValleys, filteredCandlesticks);

		List<String^>^ upWaves = waveResults->Item1;
		List<String^>^ downWaves = waveResults->Item2;

		//clear the comboboxes
		comboBox_waveUp->Items->Clear();
		comboBox_waveDown->Items->Clear();

		//add the up wave strings to the combo box
		for each(String ^ wave in upWaves)
		{
			comboBox_waveUp->Items->Add(wave);
		}

		//add the down wave strings to the combo box
		for each(String ^ wave in downWaves)
		{
			comboBox_waveDown->Items->Add(wave);
		}
	}

	/// <summary>
	/// Draws a line annotation on the chart for the selected wave.
	/// </summary>
	/// <param name="waveText">Text containing the wave dates (format: "start - end").</param>
	/// <param name="color">Color to use for the wave line annotation.</param>
	private: System::Void drawWave(String^ waveText, Color color, bool isUpWave)
	{
		//return early if no wave is selected
		if (String::IsNullOrEmpty(waveText)) return;

		//split the wave string into start and end dates
		array<String^>^ dates = waveText->Split(gcnew array<String^> { " - " }, StringSplitOptions::None);
		DateTime startDate = DateTime::Parse(dates[0]->Trim());
		DateTime endDate = DateTime::Parse(dates[1]->Trim());

		//initialize index positions
		int startIndex = -1;
		int endIndex = -1;

		//find index positions in the filtered candlesticks list
		for (int i = 0; i < filteredCandlesticks->Count; i++)
		{
			if (filteredCandlesticks[i]->Date == startDate)
				startIndex = i;
			if (filteredCandlesticks[i]->Date == endDate)
				endIndex = i;
		}

		//return if either index is invalid
		if (startIndex == -1 || endIndex == -1) return;

		//initialize peak and valley references
		PeaksAndValleys^ peakAtStart = nullptr;
		PeaksAndValleys^ valleyAtStart = nullptr;
		PeaksAndValleys^ peakAtEnd = nullptr;
		PeaksAndValleys^ valleyAtEnd = nullptr;

		//search for each possible role for both dates
		for each(PeaksAndValleys ^ pv in listPeaksAndValleys)
		{
			if (pv->Date == startDate)
			{
				if (pv->isPeak) peakAtStart = pv;
				if (pv->isValley) valleyAtStart = pv;
			}
			else if (pv->Date == endDate)
			{
				if (pv->isPeak) peakAtEnd = pv;
				if (pv->isValley) valleyAtEnd = pv;
			}
		}

		//determine wave endpoints based on direction
		PeaksAndValleys^ startPoint = nullptr;
		PeaksAndValleys^ endPoint = nullptr;

		if (isUpWave)
		{
			//up wave goes from valley to peak
			startPoint = (valleyAtStart != nullptr) ? valleyAtStart : valleyAtEnd;
			endPoint = (peakAtEnd != nullptr) ? peakAtEnd : peakAtStart;
		}
		else
		{
			//down wave goes from peak to valley
			startPoint = (peakAtStart != nullptr) ? peakAtStart : peakAtEnd;
			endPoint = (valleyAtEnd != nullptr) ? valleyAtEnd : valleyAtStart;
		}

		//return if proper roles not found
		if (startPoint == nullptr || endPoint == nullptr) return;

		//get OADate and price for drawing
		double startX = startPoint->Date.ToOADate();
		double startY = isUpWave ? startPoint->Low : startPoint->High;
		double endX = endPoint->Date.ToOADate();
		double endY = isUpWave ? endPoint->High : endPoint->Low;

		DataPoint^ startPt = gcnew DataPoint(startX, startY);
		DataPoint^ endPt = gcnew DataPoint(endX, endY);

		//generate unique name with wave type
		String^ waveTag = isUpWave ? "Up" : "Down";
		String^ seriesName = "WaveAnchorSeries_" + startIndex.ToString() + "_" + endIndex.ToString() + "_" + waveTag;
		if (!chart_candlestick->Series->IsUniqueName(seriesName)) return;

		//create a temporary point series to anchor the annotation
		Series^ tempSeries = gcnew Series(seriesName);
		tempSeries->ChartType = SeriesChartType::Point;
		tempSeries->ChartArea = "ChartArea_candlestick";
		tempSeries->IsXValueIndexed = false;
		tempSeries->Points->Add(startPt);
		tempSeries->Points->Add(endPt);
		chart_candlestick->Series->Add(tempSeries);

		//ensure the chart uses actual date values
		chart_candlestick->Series["Series_candlestick"]->IsXValueIndexed = false;

		//create the wave annotation
		LineAnnotation^ waveAnnotation = gcnew LineAnnotation();
		waveAnnotation->LineColor = color;
		waveAnnotation->LineWidth = 2;
		waveAnnotation->LineDashStyle = ChartDashStyle::Dash;
		waveAnnotation->ToolTip = startPoint->Date.ToShortDateString() + " to " + endPoint->Date.ToShortDateString();
		waveAnnotation->Visible = true;
		waveAnnotation->AxisX = chart_candlestick->ChartAreas["ChartArea_candlestick"]->AxisX;
		waveAnnotation->AxisY = chart_candlestick->ChartAreas["ChartArea_candlestick"]->AxisY;
		waveAnnotation->IsSizeAlwaysRelative = false;
		waveAnnotation->Name = "wave_" + startIndex.ToString() + "_" + endIndex.ToString() + "_" + waveTag;
		waveAnnotation->SetAnchor(tempSeries->Points[0], tempSeries->Points[1]);

		//add annotation to chart
		chart_candlestick->Annotations->Add(waveAnnotation);

		//force the chart to redraw and show the new annotations
		chart_candlestick->Invalidate();
	}

	/// <summary>
	/// Triggered when an up wave is selected from the combo box. Draws the wave annotation in green.
	/// </summary>
	private: System::Void comboBox_waveUp_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) 
	{
		//draw the selected up wave in green on the chart
		drawWave((String^)comboBox_waveUp->SelectedItem, Color::Green, true);
	}

	/// <summary>
	/// Triggered when a down wave is selected from the combo box. Draws the wave annotation in red.
	/// </summary>
	private: System::Void comboBox_waveDown_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) 
	{
		//draw the selected down wave in red on the chart
		drawWave((String^)comboBox_waveDown->SelectedItem, System::Drawing::Color::Red, false);
	}

	/// <summary>
	/// Clears all peak and valley annotations from the chart when the clear button is clicked.
	/// </summary>
	private: System::Void button_clearPeaksAndValleys_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		//call the method to clear all peak/valley annotations
		clearPeakValleyAnnotations();
	}

	/// <summary>
	/// Clears all wave line annotations from the chart when the clear button is clicked.
	/// </summary>
	private: System::Void button_clearWaves_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		//invoke the method to clear all wave annotations
		clearWaveAnnotations();
	}
	
	/// <summary>
	/// Clears wave annotations when the start date is changed by the user.
	/// </summary>
	private: System::Void dateTimePicker_start_ValueChanged(System::Object^ sender, System::EventArgs^ e) 
	{
		//clear any drawn waves since the data range has changed
		clearWaveAnnotations();
	}

	/// <summary>
	/// Removes all annotations related to peaks and valleys from the chart.
	/// </summary>
	private: System::Void clearPeakValleyAnnotations()
	{
		//loop backwards to safely remove matching annotations
		for (int i = chart_candlestick->Annotations->Count - 1; i >= 0; i--)
		{
			Annotation^ annotation = chart_candlestick->Annotations[i];
			if (annotation->Name->StartsWith("peak_") || annotation->Name->StartsWith("valley_"))
			{
				chart_candlestick->Annotations->RemoveAt(i);
			}
		}

		//force the chart to redraw and reflect changes
		chart_candlestick->Invalidate();
		chart_candlestick->Update();
	}

	/// <summary>
	/// Clears any wave annotations and wave anchor series from the chart and updates the display.
	/// Additionally, it empties the current selected values in both combo boxes.
	/// </summary>
	private: void clearWaveAnnotations()
	{
		//loop through all annotations in the chart in reverse order to avoid index issues when removing items
		for (int i = chart_candlestick->Annotations->Count - 1; i >= 0; i--)
		{
			Annotation^ annotation = chart_candlestick->Annotations[i];

			//if the annotation name starts with "wave_", remove it (these are the wave annotations)
			if (annotation->Name->StartsWith("wave_"))
			{
				chart_candlestick->Annotations->RemoveAt(i);
			}
		}

		//loop through all series in the chart in reverse order to avoid index issues when removing items
		for (int i = chart_candlestick->Series->Count - 1; i >= 0; i--)
		{
			String^ name = chart_candlestick->Series[i]->Name;

			//if the series name starts with "WaveAnchorSeries", remove it (these are the wave anchor series)
			if (name->StartsWith("WaveAnchorSeries"))
			{
				chart_candlestick->Series->RemoveAt(i);
			}
		}

		//ensure that the candlestick series is indexed by its X-values, which may have been modified
		if (chart_candlestick->Series->IndexOf("Series_candlestick") >= 0)
		{
			chart_candlestick->Series["Series_candlestick"]->IsXValueIndexed = true;
		}

		//force the chart to redraw and reflect the changes made by removing annotations and series
		chart_candlestick->Invalidate();
		chart_candlestick->Update();

		//clear the selected values in the combo boxes
		comboBox_waveUp->SelectedIndex = -1;
		comboBox_waveDown->SelectedIndex = -1; 
	}

	};
}

