import os
from pathlib import Path


def read_text(filename: str) -> str:
    """Reads the contents of a file."""
    files_dir = os.environ.get("FILES_DIR", None)
    if files_dir is None:
        raise RuntimeError("`FILES_DIR` environment variable not set")
    path = Path(files_dir) / filename
    return path.read_text()
