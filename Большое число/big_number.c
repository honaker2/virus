#include "big_number.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_string.h"


BigNumber* CreateBN(char* number_)
{
	if (number_ == NULL || strlen(number_) == 0 ||
		!IsIntString(number_))
		return NULL;

	BigNumber* bn = (BigNumber*)malloc(sizeof(BigNumber));
	if (bn == NULL)
		return NULL;

	size_t size = strlen(number_);
	if (*number_ == '-')
	{
		bn->size = size - 1;
		bn->is_negative = true;
		number_++;
	}
	else
	{
		bn->size = size;
		bn->is_negative = false;
	}

	bn->digits = (digit*)calloc(bn->size, sizeof(digit));
	if (bn->digits == NULL)
	{
		free(bn);
		return NULL;
	}

	for (size_t i = 0; i < bn->size; ++i)
		bn->digits[i] = number_[i] - '0';

	return bn;
}

void DeleteBN(BigNumber** bn_)
{
	free((*bn_)->digits);
	free(*bn_);

	*bn_ = NULL;
}

void PrintBN(BigNumber* bn_)
{
	if (bn_ == NULL)
	{
		printf("BigNumber is empty!\n");
		return;
	}

	if (bn_->is_negative)
		printf("-");

	for (size_t i = 0; i < bn_->size; ++i)
		printf("%u", bn_->digits[i]);

	printf("\n");
}

void SumBN(BigNumber* bn1_, BigNumber* bn2_)
{

	BigNumber* result = malloc(sizeof(BigNumber));
	if (result == NULL)
		return NULL;

	result->size = max(bn1_->size, bn2_->size) + 1;


	result->digits = (digit*)calloc(result->size, sizeof(digit));
	if (result->digits == NULL)
		return NULL;


	///     +  +  +
	if (bn1_->is_negative != true && bn2_->is_negative != true) {
		if (bn1_->size >= bn2_->size) {
			{
				unsigned int sub = bn1_->size - bn2_->size;
				unsigned int q1 = 0;

				for (int i = bn2_->size - 1; i > -1; --i)
				{
					unsigned int sum = bn1_->digits[i + sub] + bn2_->digits[i] + q1;

					q1 = sum / 10;

					result->digits[i + sub + 1] = sum % 10;
				}
				for (int d = bn1_->size - bn2_->size - 1; d >= 0; --d) // заполнение оставшихся чисел большего числа, с проверкой на сумму > 10
				{

					result->digits[d + 1] = (bn1_->digits[d] + q1) % 10;
					if (bn1_->digits[d] + q1 > 9) {
						q1 = (bn1_->digits[d] + q1) / 10;
					}
					else
						q1 = 0;
				}
			}
		}
	}
	if (bn1_->is_negative != true && bn2_->is_negative != true) {
		if (bn2_->size >= bn1_->size) {
			{
				unsigned int sub = bn2_->size - bn1_->size;
				unsigned int q1 = 0;

				for (int i = bn1_->size - 1; i > -1; --i)   // сложение цифр меньшего числа с цифрами большего числа на тех же местах что и у меньшего числа) 
				{
					unsigned int sum = bn1_->digits[i] + bn2_->digits[i + sub] + q1;

					q1 = sum / 10;

					result->digits[i + sub + 1] = sum % 10;

				}
				for (int d = bn2_->size - bn1_->size - 1; d >= 0; --d) // заполнение оставшихся чисел большего числа, с проверкой на сумму > 10
				{

					result->digits[d + 1] = (bn2_->digits[d] + q1) % 10;
					if (bn2_->digits[d] + q1 > 9) {
						q1 = (bn2_->digits[d] + q1) / 10;
					}
					else
						q1 = 0;
				}

			}

		}

	}


	////    -  +  -

	if (bn1_->is_negative == true && bn2_->is_negative == true) {
		if (bn1_->size >= bn2_->size) {
			{
				unsigned int sub = bn1_->size - bn2_->size;
				unsigned int q1 = 0;

				for (int i = bn2_->size - 1; i > -1; --i)
				{
					unsigned int sum = bn1_->digits[i + sub] + bn2_->digits[i] + q1;

					q1 = sum / 10;

					result->digits[i + sub + 1] = sum % 10;
				}
				for (int d = bn1_->size - bn2_->size -1; d >= 0; --d) // заполнение оставшихся чисел большего числа, с проверкой на сумму > 10
				{

					result->digits[d + 1] = (bn1_->digits[d] + q1) % 10;
					if (bn1_->digits[d] + q1 > 9) {
						q1 = (bn1_->digits[d] + q1) / 10;
					}
					else
						q1 = 0;
				}
				if (q1 != 0)
				result->digits[0] = q1;
			}
		}


	}

	if (bn1_->is_negative == true && bn2_->is_negative == true) {
		if (bn2_->size >= bn1_->size) {
			{
				unsigned int sub = bn2_->size - bn1_->size;
				unsigned int q1 = 0;

				for (int i = bn1_->size - 1; i > -1; --i)
				{
					unsigned int sum = bn2_->digits[i + sub] + bn1_->digits[i] + q1;

					q1 = sum / 10;

					result->digits[i + sub + 1] = sum % 10;
				}
				for (int d = bn2_->size - bn1_->size - 1; d >= 0; --d) // заполнение оставшихся чисел большего числа, с проверкой на сумму > 10
				{

					result->digits[d + 1] = (bn2_->digits[d] + q1) % 10;
					if (bn1_->digits[d] + q1 > 9) {
						q1 = (bn2_->digits[d] + q1) / 10;
					}
					else
						q1 = 0;
				}
			}
		}
		result->is_negative = true;

	}

	///     -   +   +   ///     +   +   -
	if (bn2_->is_negative == true && bn1_->is_negative != true) {
		if (bn2_->size == bn1_->size)
		{
			for (int i = 1; bn2_->digits[i] == bn1_->digits[i]; i++)
			{
				if (bn2_->digits[i] > bn1_->digits[i])
					bn2_->size > bn1_->size;
				else
					bn1_->size > bn2_->size;
			}
		}
		if (bn2_->size > bn1_->size) {
			{
				unsigned int sub = bn2_->size - bn1_->size;

				for (int i = bn1_->size - 1 ; i > -1; --i)
				{
					if (bn2_->digits[i + sub ] < bn1_->digits[i])
					{
						while(bn2_->digits[i+sub] < bn1_->digits[i])
						{
							int p = 1;
							for (; bn2_->digits[i + sub  - p] < 1; p++)
							{ }
							bn2_->digits[i + sub  - p] -= 1;
							bn2_->digits[i + sub + 1 - p] += 10;
							for (; bn2_->digits[i + sub + 1 - p] > 9; p--)
							{
								if (bn2_->digits[i + sub] > 9)
									break;
								bn2_->digits[i + sub + 2 - p] += 10;
								bn2_->digits[i + sub + 1 - p] -= 1;

							}
						}

					}
					unsigned int sub_2 = bn2_->digits[i + sub] - bn1_->digits[i];




					result->digits[i + sub + 1] = sub_2;
					bn2_->digits[i + sub] = bn2_->digits[i + sub] - bn1_->digits[i];
				}
				for (int d = bn2_->size - bn1_->size ; d > -1; --d) // заполнение оставшихся чисел большего числа, с проверкой на сумму > 10
				{

					result->digits[d+1] = bn2_->digits[d];
				}
			}
			result->is_negative = true;
		}
		if (bn1_->size > bn2_->size) {
			{
				unsigned int sub = bn1_->size - bn2_->size;

				for (int i = bn2_->size - 1; i > -1; --i)
				{
					if (bn1_->digits[i + sub] < bn2_->digits[i])
					{
						while (bn1_->digits[i + sub] < bn2_->digits[i])
						{
							int p = 1;
							for (; bn1_->digits[i + sub - p] < 1; p++)
							{
							}
							bn1_->digits[i + sub - p] -= 1;
							bn1_->digits[i + sub + 1 - p] += 10;
							for (; bn1_->digits[i + sub + 1 - p] > 9; p--)
							{
								if (bn1_->digits[i + sub] > 9)
									break;
								bn1_->digits[i + sub + 2 - p] += 10;
								bn1_->digits[i + sub + 1 - p] -= 1;

							}
						}

					}
					unsigned int sub_2 = bn1_->digits[i + sub] - bn2_->digits[i];




					result->digits[i + sub + 1] = sub_2;
					bn1_->digits[i + sub] = bn1_->digits[i + sub] - bn2_->digits[i];
				}
				for (int d = bn1_->size - bn2_->size; d > -1; --d) // заполнение оставшихся чисел большего числа, с проверкой на сумму > 10
				{

					result->digits[d + 1] = bn1_->digits[d];
				}
			}
		}
	}

	if (bn1_->is_negative == true && bn2_->is_negative != true) {
		if (bn1_->size == bn2_->size)
		{
			for (int i = 1; bn1_->digits[i] == bn2_->digits[i]; i++)
			{
				if (bn1_->digits[i] > bn2_->digits[i])
					bn1_->size > bn2_->size;
				else
					bn2_->size > bn1_->size;
			}
		}
		if (bn1_->size > bn2_->size) {
			{
				unsigned int sub = bn1_->size - bn2_->size;

				for (int i = bn2_->size - 1; i > -1; --i)
				{
					if (bn1_->digits[i + sub] < bn2_->digits[i])
					{
						while (bn1_->digits[i + sub] < bn2_->digits[i])
						{
							int p = 1;
							for (; bn1_->digits[i + sub - p] < 1; p++)
							{
							}
							bn1_->digits[i + sub - p] -= 1;
							bn1_->digits[i + sub + 1 - p] += 10;
							for (; bn1_->digits[i + sub + 1 - p] > 9; p--)
							{
								if (bn1_->digits[i + sub] > 9)
									break;
								bn1_->digits[i + sub + 2 - p] += 10;
								bn1_->digits[i + sub + 1 - p] -= 1;

							}
						}

					}
					unsigned int sub_2 = bn1_->digits[i + sub] - bn2_->digits[i];




					result->digits[i + sub + 1] = sub_2;
					bn1_->digits[i + sub] = bn1_->digits[i + sub] - bn2_->digits[i];
				}
				for (int d = bn1_->size - bn2_->size; d > -1; --d) // заполнение оставшихся чисел большего числа, с проверкой на сумму > 10
				{

					result->digits[d + 1] = bn1_->digits[d];
				}
			}
			result->is_negative = true;
		}
		if (bn2_->size > bn1_->size) {
			{
				unsigned int sub = bn2_->size - bn1_->size;

				for (int i = bn1_->size - 1; i > -1; --i)
				{
					if (bn2_->digits[i + sub] < bn1_->digits[i])
					{
						while (bn2_->digits[i + sub] < bn1_->digits[i])
						{
							int p = 1;
							for (; bn2_->digits[i + sub - p] < 1; p++)
							{
							}
							bn2_->digits[i + sub - p] -= 1;
							bn2_->digits[i + sub + 1 - p] += 10;
							for (; bn2_->digits[i + sub + 1 - p] > 9; p--)
							{
								if (bn2_->digits[i + sub] > 9)
									break;
								bn2_->digits[i + sub + 2 - p] += 10;
								bn2_->digits[i + sub + 1 - p] -= 1;

							}
						}

					}
					unsigned int sub_2 = bn2_->digits[i + sub] - bn1_->digits[i];




					result->digits[i + sub + 1] = sub_2;
					bn2_->digits[i + sub] = bn2_->digits[i + sub] - bn1_->digits[i];
				}
				for (int d = bn2_->size - bn1_->size; d > -1; --d) // заполнение оставшихся чисел большего числа, с проверкой на сумму > 10
				{

					result->digits[d + 1] = bn2_->digits[d];
				}
			}
		}
	}




	if (result->is_negative == true)
		printf("-");

	if (result->digits[0] == 0) {
		for (size_t i = 1; i < result->size; ++i)
			printf("%u", result->digits[i]);
	}

	if (result->digits[0] != 0) {
		for (size_t i = 0; i < result->size; ++i)
			printf("%u", result->digits[i]);
	}
	printf("\n");
	free(result);

}

void SubBN(BigNumber* bn1_, BigNumber* bn2_)
{

	BigNumber* result = malloc(sizeof(BigNumber));
	if (result == NULL)
		return NULL;

	result->size = max(bn1_->size, bn2_->size) + 1;


	result->digits = (digit*)calloc(result->size, sizeof(digit));
	if (result->digits == NULL)
		return NULL;



	///   -   -   +  

	if (bn1_->is_negative == true && bn2_->is_negative != true) {
		if (bn1_->size >= bn2_->size) {
			{
				unsigned int sub = bn1_->size - bn2_->size;
				unsigned int q1 = 0;

				for (int i = bn2_->size - 1; i > -1; --i)
				{
					unsigned int sum = bn1_->digits[i + sub] + bn2_->digits[i] + q1;

					q1 = sum / 10;

					result->digits[i + sub + 1] = sum % 10;
				}
				for (int d = bn1_->size - bn2_->size - 1; d >= 0; --d) // заполнение оставшихся чисел большего числа, с проверкой на сумму > 10
				{

					result->digits[d + 1] = (bn1_->digits[d] + q1) % 10;
					if (bn1_->digits[d] + q1 > 9) {
						q1 = (bn1_->digits[d] + q1) / 10;
					}
					else
						q1 = 0;
				}
			}
		}
		result->is_negative = true;
	}
	if (bn1_->is_negative == true && bn2_->is_negative != true) {
		if (bn2_->size >= bn1_->size) {
			{
				unsigned int sub = bn2_->size - bn1_->size;
				unsigned int q1 = 0;

				for (int i = bn1_->size - 1; i > -1; --i)   // сложение цифр меньшего числа с цифрами большего числа на тех же местах что и у меньшего числа) 
				{
					unsigned int sum = bn1_->digits[i] + bn2_->digits[i + sub] + q1;

					q1 = sum / 10;

					result->digits[i + sub + 1] = sum % 10;

				}
				for (int d = bn2_->size - bn1_->size - 1; d >= 0; --d) // заполнение оставшихся чисел большего числа, с проверкой на сумму > 10
				{

					result->digits[d + 1] = (bn2_->digits[d] + q1) % 10;
					if (bn2_->digits[d] + q1 > 9) {
						q1 = (bn2_->digits[d] + q1) / 10;
					}
					else
						q1 = 0;
				}

			}

		}
		result->is_negative = true;

	}
	///   +   -   -
	if (bn1_->is_negative != true && bn2_->is_negative == true) {
		if (bn1_->size >= bn2_->size) {
			{
				unsigned int sub = bn1_->size - bn2_->size;
				unsigned int q1 = 0;

				for (int i = bn2_->size - 1; i > -1; --i)
				{
					unsigned int sum = bn1_->digits[i + sub] + bn2_->digits[i] + q1;

					q1 = sum / 10;

					result->digits[i + sub + 1] = sum % 10;
				}
				for (int d = bn1_->size - bn2_->size - 1; d >= 0; --d) // заполнение оставшихся чисел большего числа, с проверкой на сумму > 10
				{

					result->digits[d + 1] = (bn1_->digits[d] + q1) % 10;
					if (bn1_->digits[d] + q1 > 9) {
						q1 = (bn1_->digits[d] + q1) / 10;
					}
					else
						q1 = 0;
				}
			}
		}
	}
	if (bn1_->is_negative != true && bn2_->is_negative == true) {
		if (bn2_->size >= bn1_->size) {
			{
				unsigned int sub = bn2_->size - bn1_->size;
				unsigned int q1 = 0;

				for (int i = bn1_->size - 1; i > -1; --i)   // сложение цифр меньшего числа с цифрами большего числа на тех же местах что и у меньшего числа) 
				{
					unsigned int sum = bn1_->digits[i] + bn2_->digits[i + sub] + q1;

					q1 = sum / 10;

					result->digits[i + sub + 1] = sum % 10;

				}
				for (int d = bn2_->size - bn1_->size - 1; d >= 0; --d) // заполнение оставшихся чисел большего числа, с проверкой на сумму > 10
				{

					result->digits[d + 1] = (bn2_->digits[d] + q1) % 10;
					if (bn2_->digits[d] + q1 > 9) {
						q1 = (bn2_->digits[d] + q1) / 10;
					}
					else
						q1 = 0;
				}

			}

		}

	}

	///    +  -  +
	if (bn2_->is_negative != true && bn1_->is_negative != true) {
		if (bn2_->size == bn1_->size)
		{
			for (int i = 1; bn2_->digits[i] == bn1_->digits[i]; i++)
			{
				if (bn2_->digits[i] > bn1_->digits[i])
					bn2_->size > bn1_->size;
				else
					bn1_->size > bn2_->size;
			}
		}
		if (bn2_->size > bn1_->size) {
			{
				unsigned int sub = bn2_->size - bn1_->size;

				for (int i = bn1_->size - 1; i > -1; --i)
				{
					if (bn2_->digits[i + sub] < bn1_->digits[i])
					{
						while (bn2_->digits[i + sub] < bn1_->digits[i])
						{
							int p = 1;
							for (; bn2_->digits[i + sub - p] < 1; p++)
							{
							}
							bn2_->digits[i + sub - p] -= 1;
							bn2_->digits[i + sub + 1 - p] += 10;
							for (; bn2_->digits[i + sub + 1 - p] > 9; p--)
							{
								if (bn2_->digits[i + sub] > 9)
									break;
								bn2_->digits[i + sub + 2 - p] += 10;
								bn2_->digits[i + sub + 1 - p] -= 1;

							}
						}

					}
					unsigned int sub_2 = bn2_->digits[i + sub] - bn1_->digits[i];




					result->digits[i + sub + 1] = sub_2;
					bn2_->digits[i + sub] = bn2_->digits[i + sub] - bn1_->digits[i];
				}
				for (int d = bn2_->size - bn1_->size; d > -1; --d) // заполнение оставшихся чисел большего числа, с проверкой на сумму > 10
				{

					result->digits[d + 1] = bn2_->digits[d];
				}
			}
			result->is_negative = true;
		}
		if (bn1_->size > bn2_->size) {
			{
				unsigned int sub = bn1_->size - bn2_->size;

				for (int i = bn2_->size - 1; i > -1; --i)
				{
					if (bn1_->digits[i + sub] < bn2_->digits[i])
					{
						while (bn1_->digits[i + sub] < bn2_->digits[i])
						{
							int p = 1;
							for (; bn1_->digits[i + sub - p] < 1; p++)
							{
							}
							bn1_->digits[i + sub - p] -= 1;
							bn1_->digits[i + sub + 1 - p] += 10;
							for (; bn1_->digits[i + sub + 1 - p] > 9; p--)
							{
								if (bn1_->digits[i + sub] > 9)
									break;
								bn1_->digits[i + sub + 2 - p] += 10;
								bn1_->digits[i + sub + 1 - p] -= 1;

							}
						}

					}
					unsigned int sub_2 = bn1_->digits[i + sub] - bn2_->digits[i];




					result->digits[i + sub + 1] = sub_2;
					bn1_->digits[i + sub] = bn1_->digits[i + sub] - bn2_->digits[i];
				}
				for (int d = bn1_->size - bn2_->size; d > -1; --d) // заполнение оставшихся чисел большего числа, с проверкой на сумму > 10
				{

					result->digits[d + 1] = bn1_->digits[d];
				}
			}
		}
	}
	////    -  -  -
	if (bn1_->is_negative == true && bn2_->is_negative == true) {
		if (bn1_->size == bn2_->size)
		{
			for (int i = 1; bn1_->digits[i] == bn2_->digits[i]; i++)
			{
				if (bn1_->digits[i] > bn2_->digits[i])
					bn1_->size > bn2_->size;
				else
					bn2_->size > bn1_->size;
			}
		}
		if (bn1_->size > bn2_->size) {
			{
				unsigned int sub = bn1_->size - bn2_->size;

				for (int i = bn2_->size - 1; i > -1; --i)
				{
					if (bn1_->digits[i + sub] < bn2_->digits[i])
					{
						while (bn1_->digits[i + sub] < bn2_->digits[i])
						{
							int p = 1;
							for (; bn1_->digits[i + sub - p] < 1; p++)
							{
							}
							bn1_->digits[i + sub - p] -= 1;
							bn1_->digits[i + sub + 1 - p] += 10;
							for (; bn1_->digits[i + sub + 1 - p] > 9; p--)
							{
								if (bn1_->digits[i + sub] > 9)
									break;
								bn1_->digits[i + sub + 2 - p] += 10;
								bn1_->digits[i + sub + 1 - p] -= 1;

							}
						}

					}
					unsigned int sub_2 = bn1_->digits[i + sub] - bn2_->digits[i];




					result->digits[i + sub + 1] = sub_2;
					bn1_->digits[i + sub] = bn1_->digits[i + sub] - bn2_->digits[i];
				}
				for (int d = bn1_->size - bn2_->size; d > -1; --d) // заполнение оставшихся чисел большего числа, с проверкой на сумму > 10
				{

					result->digits[d + 1] = bn1_->digits[d];
				}
			}
			result->is_negative = true;
		}
		if (bn2_->size > bn1_->size) {
			{
				unsigned int sub = bn2_->size - bn1_->size;

				for (int i = bn1_->size - 1; i > -1; --i)
				{
					if (bn2_->digits[i + sub] < bn1_->digits[i])
					{
						while (bn2_->digits[i + sub] < bn1_->digits[i])
						{
							int p = 1;
							for (; bn2_->digits[i + sub - p] < 1; p++)
							{
							}
							bn2_->digits[i + sub - p] -= 1;
							bn2_->digits[i + sub + 1 - p] += 10;
							for (; bn2_->digits[i + sub + 1 - p] > 9; p--)
							{
								if (bn2_->digits[i + sub] > 9)
									break;
								bn2_->digits[i + sub + 2 - p] += 10;
								bn2_->digits[i + sub + 1 - p] -= 1;

							}
						}

					}
					unsigned int sub_2 = bn2_->digits[i + sub] - bn1_->digits[i];




					result->digits[i + sub + 1] = sub_2;
					bn2_->digits[i + sub] = bn2_->digits[i + sub] - bn1_->digits[i];
				}
				for (int d = bn2_->size - bn1_->size; d > -1; --d) // заполнение оставшихся чисел большего числа, с проверкой на сумму > 10
				{

					result->digits[d + 1] = bn2_->digits[d];
				}
			}
		}
	}



	if (result->is_negative == true)
		printf("-");

	if (result->digits[0] == 0) {
		for (size_t i = 1; i < result->size; ++i)
			printf("%u", result->digits[i]);
	}

	if (result->digits[0] != 0) {
		for (size_t i = 0; i < result->size; ++i)
			printf("%u", result->digits[i]);
	}
	printf("\n");
	free(result);
}