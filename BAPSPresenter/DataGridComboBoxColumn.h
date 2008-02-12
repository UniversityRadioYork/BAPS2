#pragma once 

/**
	Class used to host a combobox control inside a datagrid
**/

namespace BAPSPresenter
{
	ref class DataGridComboBoxColumn : public System::Windows::Forms::DataGridColumnStyle
	{
	public:
		DataGridComboBoxColumn()
		{
			/** Create the combo box for the column **/
			comboBox = gcnew System::Windows::Forms::ComboBox();
			/** Start with it hidden, we only show it when editing **/
			comboBox->Visible = false;
		}
		System::Windows::Forms::ComboBox^ getComboBox()
		{
			return comboBox;
		}

	protected:
		virtual void Abort(int /*rowNum*/) override
		{
			/** If we abort we reset the state of this column without saving **/
			isEditing = false;
			comboBox->SelectedIndexChanged -= gcnew System::EventHandler(this, &DataGridComboBoxColumn::ComboBoxValueChanged);
			Invalidate();
		}

		virtual bool Commit(System::Windows::Forms::CurrencyManager^ dataSource, int rowNum) override
		{
			comboBox->Bounds = System::Drawing::Rectangle::Empty;

			comboBox->SelectedIndexChanged -= gcnew System::EventHandler(this, &DataGridComboBoxColumn::ComboBoxValueChanged);
			/** We have nothing to commit if we are not editing **/
			if (!isEditing)
			{
				return true;
			}
			/** Ensure this happens only once when it is needed **/
			isEditing = false;
			/** Lots of things can go wrong here...
				Wrong type in the underlying datatable
				No entried in the combo box
				...
			**/
			try
			{
				int value = comboBox->SelectedIndex; 
				/** Update the underlying datatable **/
				SetColumnValueAtRow(dataSource, rowNum, value);
			}
			catch (System::Exception^)
			{
				Abort(rowNum);
				return false;
			}

			Invalidate();
			return true;
		}

		virtual void Edit(System::Windows::Forms::CurrencyManager^ source,
				int rowNum,
				System::Drawing::Rectangle bounds,
				bool /*readOnly*/,
				System::String^ /*instantText*/,
				bool cellIsVisible) override
		{
			/** Get the current value from the underlying datatable **/
			System::Object^ temp = GetColumnValueAtRow(source, rowNum);
			int value = 0;
			/** Make sure we have a valid value: default-0 **/
			if (temp != nullptr && temp != System::DBNull::Value)
			{
				value = safe_cast<int>(temp);
			}
			if (!isEditing && cellIsVisible)
			{
				/** When we are not already editing and can see the cell
					draw the combo box and add the event handler
				**/
				comboBox->Bounds = System::Drawing::Rectangle
											(bounds.X + 2, bounds.Y + 2,
												bounds.Width - 4, bounds.Height - 4);
				comboBox->SelectedIndex= value;
				comboBox->Visible = true;
				comboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &DataGridComboBoxColumn::ComboBoxValueChanged);
			}
			else if (!isEditing)
			{
				/** If we cant see the cell but are editing it then just set-up the
					combo box and make it invisible
				**/
				comboBox->SelectedIndex = value;
				comboBox->Visible = false;
			}

			if (comboBox->Visible)
			{
				/** If we can see the box we need it to be repainted **/
				DataGridTableStyle->DataGrid->Invalidate(bounds);
			}
		}

		virtual System::Drawing::Size GetPreferredSize(System::Drawing::Graphics^ /*g*/, System::Object^ /*value*/) override
		{
			return System::Drawing::Size(100, comboBox->PreferredHeight + 4);
		}

		virtual int GetMinimumHeight() override
		{
			return comboBox->PreferredHeight + 4;
		}

		virtual int GetPreferredHeight(System::Drawing::Graphics^ /*g*/, System::Object^ /*value*/) override
		{
			return comboBox->PreferredHeight + 4;
		}

		virtual void Paint(System::Drawing::Graphics^ g, System::Drawing::Rectangle bounds, System::Windows::Forms::CurrencyManager^ source, int rowNum) override
		{
			Paint(g, bounds, source, rowNum, false);
		}

		virtual void Paint(System::Drawing::Graphics^ g, System::Drawing::Rectangle bounds, System::Windows::Forms::CurrencyManager^ source, int rowNum, bool alignToRight) override
		{
			Paint(g, bounds, source, rowNum, System::Drawing::Brushes::Red, System::Drawing::Brushes::Blue, alignToRight);
		}

		virtual void Paint(System::Drawing::Graphics^ g, System::Drawing::Rectangle bounds, System::Windows::Forms::CurrencyManager^ source, int rowNum, System::Drawing::Brush^ backBrush, System::Drawing::Brush^ foreBrush, bool /*alignToRight*/) override
		{
			/** When we are not editing the value we draw it as follows **/
			/** Get the current value **/
			System::Object^ temp = GetColumnValueAtRow(source, rowNum);
			int value = 0;
			/** See if a valid value is in the datatable **/
			if (temp != nullptr && temp != System::DBNull::Value)
			{
				value = safe_cast<int>(temp);
			}
			/** Draw the background and fill it with backBrush colour **/
			System::Drawing::Rectangle rect = bounds;
			g->FillRectangle(backBrush, rect);
			/** Make a smaller rectangle inside for the text **/
			rect.Offset(0, 2);
			rect.Height -= 2;
			/** Draw the textual value into the box **/
			g->DrawString(comboBox->Items[value]->ToString(),
						  this->DataGridTableStyle->DataGrid->Font, 
						  foreBrush, 
						  rect);
		}

		virtual void SetDataGridInColumn(System::Windows::Forms::DataGrid^ value) override
		{
			/** Register the combo box as a child of the datagrid or it will
				never be seen (all controls must be hosted in another control)
			**/
			DataGridColumnStyle::SetDataGridInColumn(value);
			if (comboBox->Parent != nullptr)
			{
				comboBox->Parent->Controls->Remove(comboBox);
			}
			if (value != nullptr)
			{
				value->Controls->Add(comboBox);
			}
		}

	private:
		void ComboBoxValueChanged(System::Object^ /*sender*/, System::EventArgs^ /*e*/)
		{
			/** If the combo box has its value changed then we are editing **/
			this->isEditing = true;
			DataGridColumnStyle::ColumnStartedEditing(comboBox);
		}

		/** The combobox being hosted in this column **/
		System::Windows::Forms::ComboBox^ comboBox;

		/** Flag used to determine if an edit is in progress so that changes can be stored out to the
			datagrid
		**/
		bool  isEditing;

	};
};