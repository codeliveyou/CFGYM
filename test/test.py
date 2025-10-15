# import pandas as pd
# from concurrent.futures import ProcessPoolExecutor
# from datetime import datetime
# import os
# from collections import defaultdict

# input_file_path = "input.xlsx"
# output_file_path = "test_output.xlsx"

# # Read the Excel file
# df = pd.read_excel(input_file_path, sheet_name="Data")
# df.columns = df.columns.str.strip()

# # Optimize data types
# df["Customer ID"] = df["Customer ID"].astype('category')
# df["Amount"] = pd.to_numeric(df["Amount"], downcast='float')

# def process_customer(customer_id):
#     # Function logic remains the same
#     customer_df = df[df["Customer ID"] == customer_id].sort_values("Date").head(18)
    
#     key_value = defaultdict(list)
#     group_rows = []
    
#     for index, row in customer_df.iterrows():
#         amount = row["Amount"]
            
#         temp_value = key_value.copy()
#         for key in list(key_value.keys()):
#             new_key = key + amount
#             if new_key not in key_value:
#                 key_value[new_key] = temp_value[key] + [index]
#             elif key_value[new_key][0] > key_value[key][0]:
#                 key_value[new_key] = temp_value[key] + [index]
        
#         if amount not in key_value:
#             key_value[amount] = [index]
        
#     for group_key, indices in key_value.items():
#         for index in indices:
#             group_rows.append({
#                 "Customer ID": customer_id,
#                 "Key Amount": group_key,
#                 "Invoice Number": customer_df.at[index, "Invoice Number"],
#                 "Date": customer_df.at[index, "Date"].date(),
#                 "Amount": customer_df.at[index, "Amount"],
#             })
    
#     return group_rows

# if __name__ == '__main__':
#     num_cpus = os.cpu_count()
#     num_tasks = len(df['Customer ID'].cat.categories)
#     chunksize = max(1, num_tasks // (num_cpus * 4))
    
#     start_time = datetime.now()
#     all_group_rows = []
#     # with ProcessPoolExecutor() as executor:
#     #     results = list(executor.map(process_customer, df["Customer ID"].cat.categories, chunksize=chunksize))
        
#     with ProcessPoolExecutor(max_workers=1) as executor:
#         results = list(executor.map(process_customer, df["Customer ID"].cat.categories))

#     all_group_rows = [row for result in results for row in result]

#     output_df = pd.DataFrame(all_group_rows)
#     print(output_df.columns)

#     # Reorganize columns
#     output_df = output_df[["Customer ID", "Key Amount", "Invoice Number", "Date", "Amount"]]

#     output_df.to_csv('output_file.csv', index=False)
    
#     # Write to Excel
#     # start_time = datetime.now()
#     # with pd.ExcelWriter(output_file_path, engine="openpyxl") as writer:
#     #     output_df.to_excel(writer, index=False, sheet_name="Output2")
        
#     print(datetime.now() - start_time)

#     # print(f"Filtered Output2 written to {output_file_path}")


values = [1, 2, 5, 6, 8, 10]
keys   = [0, 1, 2, 3, 4, 5]

keyNumber = len(values)

bit = 1 << keyNumber

dic = {}

for b in range(bit):
    tmpKeyList = []
    tmpSum = 0
    for i in range(keyNumber):
        if (b & (1 << i)) != 0:
            tmpKeyList.append(i)
            tmpSum += values[i]
            tmpKeyList.append(keys[i])
    dic[tmpSum] = tmpKeyList

print(dic)

