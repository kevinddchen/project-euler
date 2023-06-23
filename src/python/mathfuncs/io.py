import os
from pathlib import Path


def read_text(filename: str) -> str:
    """Reads the text contents of a file. The file is assumed to be in the
    `FILES_DIR` directory.

    Args:
        filename: Name of file to read.

    Returns:
        Text contents of file.

    Raises:
        RuntimeError: If `FILES_DIR` environment variable is not set.
    """

    files_dir = os.environ.get("FILES_DIR", None)
    if files_dir is None:
        raise RuntimeError("`FILES_DIR` environment variable not set")

    path = Path(files_dir) / filename
    return path.read_text()
