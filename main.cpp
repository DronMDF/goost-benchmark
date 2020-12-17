#include <iostream>
#include <memory>
#include <vector>
#include <chrono>
#include <openssl/evp.h>
#include <openssl/rand.h>

using namespace std;

using EVP_CIPHER_CTX_ptr = unique_ptr<EVP_CIPHER_CTX, decltype(&::EVP_CIPHER_CTX_free)>;

static const unsigned int KEY_SIZE = 32;
static const unsigned int BLOCK_SIZE = 16;

void gen_params(uint8_t key[KEY_SIZE], uint8_t iv[BLOCK_SIZE])
{
	int rc = RAND_bytes(key, KEY_SIZE);
	if (rc != 1) {
		throw runtime_error("RAND_bytes key failed");
	}

	rc = RAND_bytes(iv, BLOCK_SIZE);
	if (rc != 1) {
		throw runtime_error("RAND_bytes for iv failed");
	}
}

void aes_encrypt(const uint8_t key[KEY_SIZE], const uint8_t iv[BLOCK_SIZE], const vector<uint8_t> &ptext, vector<uint8_t> &ctext)
{
	EVP_CIPHER_CTX_ptr ctx(EVP_CIPHER_CTX_new(), ::EVP_CIPHER_CTX_free);
	int rc = EVP_EncryptInit_ex(ctx.get(), EVP_aes_256_cbc(), NULL, key, iv);
	if (rc != 1) {
		throw runtime_error("EVP_EncryptInit_ex failed");
	}

	// Cipher text expands upto BLOCK_SIZE
	ctext.resize(ptext.size()+BLOCK_SIZE);
	int out_len1 = (int)ctext.size();

	rc = EVP_EncryptUpdate(ctx.get(), &ctext[0], &out_len1, &ptext[0], (int)ptext.size());
	if (rc != 1) {
		throw runtime_error("EVP_EncryptUpdate failed");
	}
	int out_len2 = (int)ctext.size() - out_len1;
	rc = EVP_EncryptFinal_ex(ctx.get(), &ctext[out_len1], &out_len2);
	if (rc != 1) {
		throw runtime_error("EVP_EncryptFinal_ex failed");
	}

	// Set cipher text size now that we know it
	ctext.resize(out_len1 + out_len2);
}

void aes_decrypt(const uint8_t key[KEY_SIZE], const uint8_t iv[BLOCK_SIZE], const vector<uint8_t> &ctext, vector<uint8_t> &rtext)
{
	EVP_CIPHER_CTX_ptr ctx(EVP_CIPHER_CTX_new(), ::EVP_CIPHER_CTX_free);
	int rc = EVP_DecryptInit_ex(ctx.get(), EVP_aes_256_cbc(), NULL, key, iv);
	if (rc != 1) {
		throw runtime_error("EVP_DecryptInit_ex failed");
	}

	// Recovered text contracts upto BLOCK_SIZE
	rtext.resize(ctext.size());
	int out_len1 = (int)rtext.size();

	rc = EVP_DecryptUpdate(ctx.get(), &rtext[0], &out_len1, &ctext[0], (int)ctext.size());
	if (rc != 1) {
		throw runtime_error("EVP_DecryptUpdate failed");
	}

	int out_len2 = (int)rtext.size() - out_len1;
	rc = EVP_DecryptFinal_ex(ctx.get(), &rtext[out_len1], &out_len2);
	if (rc != 1) {
		throw runtime_error("EVP_DecryptFinal_ex failed");
	}

	// Set recovered text size now that we know it
	rtext.resize(out_len1 + out_len2);
}

int main(int, char **)
{
	// Load the necessary cipher
	EVP_add_cipher(EVP_aes_256_cbc());

	// plaintext, ciphertext, recovered text
	constexpr size_t datasize = 1024 * 1024 * 1024;
	vector<uint8_t> ptext(datasize);
	vector<uint8_t> ctext(datasize);
	vector<uint8_t> rtext(datasize);

	uint8_t key[KEY_SIZE];
	uint8_t iv[BLOCK_SIZE];
	gen_params(key, iv);

	const auto start_time = chrono::high_resolution_clock::now();

	aes_encrypt(key, iv, ptext, ctext);

	const auto middle_time = chrono::high_resolution_clock::now();

	aes_decrypt(key, iv, ctext, rtext);

	const auto end_time = chrono::high_resolution_clock::now();
	const chrono::duration<double> encryption_time = middle_time - start_time;
	const chrono::duration<double> decryption_time = end_time - middle_time;

	cout << "Encryption: " << static_cast<size_t>(datasize / encryption_time.count() / 1024) << " kbps" << endl;
	cout << "Decryption: " << static_cast<size_t>(datasize / decryption_time.count() / 1024) << " kbps" << endl;

	return 0;
}
