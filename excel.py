from xlrd import open_workbook,cellname
from xlwt import Workbook
book1 = Workbook()
sheet1 = book1.add_sheet('Sheet 1')
book = open_workbook('worksheet.xls')
sheet = book.sheet_by_index(0)
x=0
print sheet.name
print sheet.nrows
print sheet.ncols
for row_index in range(sheet.nrows):
  for col_index in range(sheet.ncols):
    print cellname(row_index,col_index),'-',
    print sheet.cell(row_index,col_index).value
    b = sheet.cell(row_index,col_index).value
    sheet1.write(row_index,col_index,b)	  
    x = x + sheet.cell(row_index,col_index).value
    y=x/(sheet.ncols)
  sheet1.write(row_index,col_index+1,y)
  print y
book1.save ('sime.xls')

	